"""Use existing Cocos atlas pages; never emit individual sprite PNGs.
Rotated pages get one lossless orientation adapter because AtlasTexture has no rotation.
Scene atlas regions are embedded subresources, not thousands of .tres files.
"""
from pathlib import Path
import json,plistlib,re,hashlib,shutil
from PIL import Image
P=Path(__file__).resolve().parents[1]; A=P/'assets/master'
def nums(s):return list(map(int,re.findall(r'-?\d+',s)))
def resource(p):return 'res://'+str(p.relative_to(P))
def main():
 if not (A/'frames').exists():
  if (A/'atlas_frames.json').exists():
   print('Already uses existing atlases; rebuild through import_master.py to refresh.')
   return
  raise RuntimeError('Run import_master.py first')
 frames={};legacy={};rotated={}
 def add(name,page,x,y,w,h,sw,sh,sx,sy,rot):
  if rot:
   if page not in rotated:
    target=A/'atlases'/(hashlib.sha256(str(page.relative_to(A)).encode()).hexdigest()[:12]+'_rotated.png')
    target.parent.mkdir(exist_ok=True);Image.open(page).transpose(Image.Transpose.ROTATE_90).save(target);rotated[page]=target
   height=Image.open(page).width
   x,y=y,height-x-h
   page=rotated[page]
  frames[name]={'page':resource(page),'region':[x,y,w,h],'margin':[sx,sy,sw-w,sh-h]}
 for f in sorted(A.rglob('*.plist')):
  try:
   d=plistlib.loads(f.read_bytes());meta=d.get('metadata',{});page=f.parent/meta.get('textureFileName',meta.get('realTextureFileName',f.with_suffix('.png').name));fs=d['frames']
   if not page.exists():continue
  except (ValueError,KeyError):continue
  for name,fr in fs.items():
   if 'frame' in fr:
    x,y,w,h=nums(fr['frame']);sw,sh=nums(fr['sourceSize']);sx,sy,_,_=nums(fr['sourceColorRect']);rot=fr.get('rotated',False)
   else:
    x,y,w,h=nums(fr['textureRect']);sw,sh=nums(fr['spriteSourceSize']);ox,oy=nums(fr.get('spriteOffset','{0,0}'));sx=int((sw-w)/2+ox);sy=int((sh-h)/2-oy);rot=fr.get('textureRotated',False)
   add(name,page,x,y,w,h,sw,sh,sx,sy,rot)
 for key,fr in (json.loads((A/'atlas_regions.json').read_text()) if (A/'atlas_regions.json').exists() else {}).items():
  atlas,name=key.split(':',1)
  if Path(atlas).name not in ['car_new_0_1.atlas','car_new_0_6.atlas']:continue
  x,y,w,h=fr['rect'];sw,sh=fr['size'];sx,oy=fr['offset'];add(name+'.png',P/fr['page'].removeprefix('res://'),x,y,w,h,sw,sh,sx,sh-oy-h,fr['rotate'])
 # Recover exact old case-collision paths and assert every decoded sprite is identical.
 verified=0
 for name,fr in frames.items():
  old=A/'frames'/name
  if not old.exists():old=old.with_name(old.stem+'__'+hashlib.sha256(name.encode()).hexdigest()[:8]+old.suffix)
  if not old.exists():continue
  x,y,w,h=fr['region'];sx,sy,mw,mh=fr['margin'];full=Image.new('RGBA',(w+mw,h+mh));full.paste(Image.open(P/fr['page'].removeprefix('res://')).convert('RGBA').crop((x,y,x+w,y+h)),(sx,sy))
  prior=Image.open(old).convert('RGBA')
  if full.size!=prior.size or full.tobytes()!=prior.tobytes():raise RuntimeError('Atlas pixel mismatch: '+name)
  legacy[resource(old)]=name;verified+=1
 missing=[resource(f) for f in (A/'frames').rglob('*.png') if resource(f) not in legacy]
 if missing:raise RuntimeError('Unmapped sprites '+str(missing))
 (A/'atlas_frames.json').write_text(json.dumps(frames,separators=(',',':')))
 # Inline AtlasTexture resources, shared original atlas pages per scene.
 scenes=0
 for scene in (P/'scenes/native').rglob('*.tscn'):
  text=scene.read_text();defs=[];pages={};replacements={}
  def replace(m):
   path,id=m.groups()
   if path not in legacy:return m.group(0)
   fr=frames[legacy[path]];page=fr['page']
   if page not in pages:pages[page]='atlas_page_'+str(len(pages))
   sub='atlas_sprite_'+id;replacements[id]=sub
   rect=lambda r:'Rect2('+', '.join(map(str,r))+')'
   defs.append('[sub_resource type="AtlasTexture" id="'+sub+'"]\natlas = ExtResource("'+pages[page]+'")\nregion = '+rect(fr['region'])+'\nmargin = '+rect(fr['margin'])+'\nfilter_clip = true\n')
   return ''
  text=re.sub(r'\[ext_resource type="Texture2D" path="([^"]+)" id="([^"]+)"\]',replace,text)
  if not defs:continue
  for id,sub in replacements.items():text=text.replace('ExtResource("'+id+'")','SubResource("'+sub+'")')
  page_defs='\n'.join('[ext_resource type="Texture2D" path="'+page+'" id="'+id+'"]' for page,id in pages.items())
  # External definitions must precede ALL subresources.
  idx=text.find('[sub_resource')
  if idx<0:idx=text.find('[node ')
  text=text[:idx]+page_defs+'\n\n'+'\n'.join(defs)+'\n'+text[idx:]
  text=re.sub(r'load_steps=\d+','load_steps='+str(len(re.findall(r'\[(?:ext_resource|sub_resource) ',text))+1),text,count=1)
  scene.write_text(text);scenes+=1
 # Rewrite runtime lookups to a cached atlas registry.
 for script in (P/'solitaire/native').glob('*.gd'):
  if script.name=='atlas.gd':continue
  text=script.read_text()
  if 'res://assets/master/frames/' not in text:continue
  text=text.replace('res://assets/master/frames/','')
  if script.name=='card.gd':text=text.replace('load(prefix +','MasterAtlas.texture(prefix +')
  else:
   text=re.sub(r'load\(("(?:ui_btn_close[01]\.png|card_bg_%d\.png|ui_switch%d\.png|daily/[^"\n]+|Money/[^"\n]+)"[^\n]*?)\)',r'MasterAtlas.texture(\1)',text)
   text=text.replace('load("" +','MasterAtlas.texture("" +')
   text=text.replace('ResourceLoader.exists(path)','MasterAtlas.has_frame(path)').replace('image.texture = load(path)','image.texture = MasterAtlas.texture(path)')
  script.write_text(text)
 # Keep runtime assets referenced by scenes/scripts, registry, and dynamic directories.
 keep={P/fr['page'].removeprefix('res://') for fr in frames.values()}
 for root in [P/'scenes',P/'solitaire',P/'tests',P/'tools']:
  for f in root.rglob('*'):
   if f.suffix not in ['.gd','.tscn','.py']:continue
   for ref in re.findall(r'res://assets/master/([^"\s\)]+)',f.read_text()):
    target=A/ref
    if target.is_file():keep.add(target)
 for directory in ['data','music','game','spine']:
  keep.update(f for f in (A/directory).rglob('*') if f.is_file() and f.suffix!='.import')
 for f in (A/'baked').glob('*.gz'):
  import gzip
  d=json.loads(gzip.decompress(f.read_bytes()));keep.update(P/(d['atlas_dir']+'/'+str(a['page'])).removeprefix('res://') for a in d['attachments'])
 def keep_icons(item):
  if isinstance(item,dict):
   if isinstance(item.get('icon'),str):
    for directory in ['HD1','level']:keep.add(A/directory/item['icon'])
   for value in item.values():keep_icons(value)
  elif isinstance(item,list):
   for value in item:keep_icons(value)
 for source in (A/'data').glob('*.json'):
  try:keep_icons(json.loads(source.read_text()))
  except ValueError:pass
 keep.update(A/'img'/name for name in ['img_music_on.png','img_music_off.png'])
 keep.update(A/n for n in ['atlas_frames.json','atlas_regions.json','manifest.json','localization_bindings.json','chinese.tres'])
 removed=0
 for f in list(A.rglob('*')):
  if not f.is_file() or f in keep or (f.suffix=='.import' and f.with_suffix('') in keep):continue
  f.unlink();removed+=1
 for f in sorted(A.rglob('*'),key=lambda x:len(x.parts),reverse=True):
  if f.is_dir() and not any(f.iterdir()):f.rmdir()
 print(json.dumps({'verified_identical_sprites':verified,'atlas_frames':len(frames),'scenes':scenes,'rotation_adapter_pages':len(rotated),'removed_files':removed}))
if __name__=='__main__':main()
