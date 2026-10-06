"""NewHD 1080x1920 CSD assets and timelines to native Godot scenes.
The reference tree is an immutable git archive, never the Cocos working tree.
"""
from pathlib import Path
import json,plistlib,shutil,re,math,hashlib,xml.etree.ElementTree as E
from PIL import Image
P=Path(__file__).resolve().parents[1]
S=P.parent/'reference/NewHD'
A=P/'assets/newhd';SC=P/'scenes/newhd';A.mkdir(parents=True,exist_ok=True);SC.mkdir(parents=True,exist_ok=True)
def q(s):return json.dumps(s,ensure_ascii=False)
def n(x):return str(round(float(x),5))
def v(x,y):return f'Vector2({n(x)}, {n(y)})'
def nums(s):return list(map(float,re.findall(r'-?\d+(?:\.\d+)?',s)))
def rgba(e,a=1):
 d=e.attrib if e is not None else {};return 'Color('+', '.join(n(float(d.get(k,255))/255*(a if k=='A' else 1)) for k in 'RGBA')+')'
missing=[];unsupported=[];timeline_report={};frames={}
loose_images={}
def assets():
 shutil.copytree(S/'Resources',A,dirs_exist_ok=True)
 for f in (S/'cocosstudio').rglob('*'):
  if f.is_file() and f.suffix.lower() in ['.png','.jpg','.fnt','.ttf','.mp3','.wav']:
   t=A/f.relative_to(S/'cocosstudio')
   if not t.exists():t.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(f,t)
 # Original .png files can contain TIFF bytes; Godot requires PNG encoding.
 for texture in A.rglob('*.png'):
  if texture.read_bytes()[:4] in [b'II*\x00',b'MM\x00*']:
   Image.open(texture).convert('RGBA').save(texture,format='PNG')
 (A/'frames').mkdir(exist_ok=True)
 for f in A.rglob('*'):
  if f.is_file() and f.suffix.lower() in ['.png','.jpg','.jpeg'] and 'frames' not in f.relative_to(A).parts:
   loose_images.setdefault(f.name,[]).append(f)
 case_names={}
 for f in A.rglob('*.plist'):
  try:
   for name in plistlib.loads(f.read_bytes()).get('frames',{}):case_names.setdefault(name.lower(),set()).add(name)
  except (ValueError,KeyError):pass
 for f in sorted(A.rglob('*.plist')):
  try:d=plistlib.loads(f.read_bytes());fs=d['frames'];meta=d.get('metadata',{});sheet=Image.open(f.parent/meta.get('textureFileName',meta.get('realTextureFileName',f.with_suffix('.png').name)))
  except (KeyError,FileNotFoundError,ValueError):continue
  for name,fr in fs.items():
   if 'frame' in fr:x,y,w,h=map(int,nums(fr['frame']));rot=fr.get('rotated',False);sw,sh=map(int,nums(fr['sourceSize']));sx,sy,_,_=map(int,nums(fr['sourceColorRect']))
   else:x,y,w,h=map(int,nums(fr['textureRect']));rot=fr.get('textureRotated',False);sw,sh=map(int,nums(fr['spriteSourceSize']));ow,oh=nums(fr.get('spriteOffset','{0,0}'));sx=int((sw-w)/2+ow);sy=int((sh-h)/2-oh)
   im=sheet.crop((x,y,x+(h if rot else w),y+(w if rot else h)))
   if rot:im=im.transpose(Image.Transpose.ROTATE_90)
   full=Image.new('RGBA',(sw,sh));full.paste(im,(sx,sy))
   output=Path(name)
   if len(case_names[name.lower()])>1:output=output.with_name(output.stem+'__'+hashlib.sha256(name.encode()).hexdigest()[:8]+output.suffix)
   t=A/'frames'/output;t.parent.mkdir(parents=True,exist_ok=True);full.save(t);frames[name]=str(t.relative_to(P))
 # Full original atlases used for card skins; region metadata retains trim and rotation.
 atlas={}
 for f in A.rglob('*.atlas'):
  page=None;name=None;props={};ispage=False
  def save():
   if not name or 'xy' not in props or page is None:return
   x,y=map(int,props['xy'].split(','));w,h=map(int,props['size'].split(','));ow,oh=map(int,props.get('orig',props['size']).split(','));ox,oy=map(int,props.get('offset','0,0').split(','));rot=props.get('rotate')=='true'
   atlas[str(f.relative_to(A))+':'+name]={'page':'res://'+str(page.relative_to(P)),'rect':[x,y,w,h],'size':[ow,oh],'offset':[ox,oy],'rotate':rot}
   if f.name not in ['car_new_0_1.atlas','car_new_0_6.atlas']:return
   sheet=Image.open(page);im=sheet.crop((x,y,x+(h if rot else w),y+(w if rot else h)))
   if rot:im=im.transpose(Image.Transpose.ROTATE_90)
   full=Image.new('RGBA',(ow,oh));full.paste(im,(ox,oh-oy-im.height))
   filename=name+'.png'
   output=Path(filename)
   if len(case_names.get(filename.lower(),[]))>1:output=output.with_name(output.stem+'__'+hashlib.sha256(filename.encode()).hexdigest()[:8]+output.suffix)
   t=A/'frames'/output;t.parent.mkdir(parents=True,exist_ok=True);full.save(t);frames[filename]=str(t.relative_to(P))
  for line in f.read_text().splitlines():
   if not line.strip():save();name=None;props={};ispage=True
   elif not line[0].isspace() and ':' not in line:
    if ispage or page is None:page=f.parent/line.strip();ispage=False
    else:save();name=line.strip();props={}
   elif ':' in line and line[0].isspace():k,val=line.strip().split(':',1);props[k]=val.strip()
  save()
 (A/'atlas_regions.json').write_text(json.dumps(atlas,ensure_ascii=False,separators=(',',':')))
 (A/'chinese.tres').write_text('[gd_resource type="SystemFont" format=3]\n[resource]\nfont_names = PackedStringArray("PingFang SC", "Heiti SC", "Microsoft YaHei", "Noto Sans CJK SC")\n')

def easing(k,x):
 if k==0:return x
 if k==1:return 1-math.cos(x*math.pi/2)
 if k==2:return math.sin(x*math.pi/2)
 if k==3:return (1-math.cos(x*math.pi))/2
 if 4<=k<=15:
  p=2+(k-4)//3;m=(k-4)%3
  return x**p if m==0 else (1-(1-x)**p if m==1 else (2**(p-1)*x**p if x<.5 else 1-(-2*x+2)**p/2))
 if k in [16,17,18]:
  f=lambda t:0 if t==0 else 2**(10*(t-1))
  return f(x) if k==16 else 1-f(1-x) if k==17 else f(2*x)/2 if x<.5 else 1-f(2-2*x)/2
 if k in [19,20,21]:
  f=lambda t:1-math.sqrt(max(0,1-t*t));return f(x) if k==19 else 1-f(1-x) if k==20 else f(x*2)/2 if x<.5 else 1-f(2-x*2)/2
 if k in [22,23,24]:
  def f(t):
   if t in [0,1]:return t
   return -2**(10*(t-1))*math.sin((t-1-.075)*2*math.pi/.3)
  return f(x) if k==22 else 1-f(1-x) if k==23 else f(x*2)/2 if x<.5 else 1-f(2-x*2)/2
 if k in [25,26,27]:
  def f(t):return t*t*(2.70158*t-1.70158)
  return f(x) if k==25 else 1-f(1-x) if k==26 else f(2*x)/2 if x<.5 else 1-f(2-2*x)/2
 if k in [28,29,30]:
  def b(t):
   if t<1/2.75:return 7.5625*t*t
   if t<2/2.75:return 7.5625*(t-1.5/2.75)**2+.75
   if t<2.5/2.75:return 7.5625*(t-2.25/2.75)**2+.9375
   return 7.5625*(t-2.625/2.75)**2+.984375
  return 1-b(1-x) if k==28 else b(x) if k==29 else (1-b(1-2*x))/2 if x<.5 else (1+b(2*x-1))/2
 unsupported.append(('easing',k));return x

def import_scene(f):
 r=E.parse(f);root=r.find('.//ObjectData')
 if root is None:return
 rel=f.relative_to(S/'cocosstudio').with_suffix('.tscn');target=SC/rel;target.parent.mkdir(parents=True,exist_ok=True)
 resources={};subs=[];nodes=[];tags={};count=0;used_names={}
 def res(path,typ='Texture2D'):
  key=(path,typ)
  if key not in resources:resources[key]=str(len(resources)+1)
  return f'ExtResource("{resources[key]}")'
 def texture(e):
  if e is None:return None
  path=e.get('Path','').replace('\\','/')
  if not path or Path(path).suffix.lower() not in ['.png','.jpg','.jpeg']:return None
  t=A/path
  if e.get('Type')=='PlistSubImage' or not t.exists():t=P/frames[path] if path in frames else A/'frames'/path
  if not t.exists():t=A/'frames'/Path(path).name
  if not t.exists():
   candidates=loose_images.get(Path(path).name,[])
   if candidates and len({hashlib.sha256(p.read_bytes()).digest() for p in candidates})==1:t=candidates[0]
  if not t.exists():missing.append((str(rel),path));return None
  return res('res://'+str(t.relative_to(P)))
 def visit(e,parent,psize):
  nonlocal count
  count+=1;original_name=e.get('Name','Layer');name=original_name.replace('/','_');sz=e.find('Size');pos=e.find('Position');anc=e.find('AnchorPoint');sc=e.find('Scale')
  # Cocos permits same-named siblings; PackedScene paths must be unique.
  # Otherwise Godot replaces the first node and silently loses its children.
  names=used_names.setdefault(parent,set());base=name;suffix=2
  while name in names:name=f'{base}__{suffix}';suffix+=1
  names.add(name)
  w=float(sz.get('X',0)) if sz is not None else 0;h=float(sz.get('Y',0)) if sz is not None else 0;x=float(pos.get('X',0)) if pos is not None else 0;y=float(pos.get('Y',0)) if pos is not None else 0;ax=float(anc.get('ScaleX',0)) if anc is not None else 0;ay=float(anc.get('ScaleY',0)) if anc is not None else 0
  typ=e.get('ctype','');tx=texture(e.find('FileData'));instance=None
  if typ=='ProjectNodeObjectData':
   fd=e.find('FileData');path=fd.get('Path','') if fd is not None else ''
   if path and (S/'cocosstudio'/path).exists():instance=res('res://scenes/newhd/'+str(Path(path).with_suffix('.tscn')),'PackedScene')
  if 'Button' in typ:t='TextureButton'
  elif typ in ['TextObjectData','TextBMFontObjectData','TextFieldObjectData']:t='Label'
  elif typ=='TextAtlasObjectData':t='Control'
  elif typ in ['ScrollViewObjectData','ListViewObjectData','PageViewObjectData']:t='ScrollContainer'
  elif typ=='LoadingBarObjectData':t='TextureProgressBar'
  elif tx:t='NinePatchRect' if e.get('Scale9Enable')=='True' else 'TextureRect'
  elif int(e.get('ComboBoxIndex',0))==1:t='ColorRect'
  else:t='Control'
  props=['layout_mode = 0',f'mouse_filter = {0 if t in ["TextureButton","ScrollContainer"] else 2}']
  path='.' if parent is None else (name if parent=='.' else parent+'/'+name)
  if parent is None:props+=[f'offset_right = {n(w)}',f'offset_bottom = {n(h)}','script = '+res('res://solitaire/newhd/cocos_scene.gd','Script'), f'metadata/source_scene = {q(str(rel.with_suffix("")).removeprefix("ui/"))}']
  else:
   props += [f'offset_left = {n(x-ax*w)}',f'offset_top = {n(psize[1]-y-(1-ay)*h)}',f'offset_right = {n(x+(1-ax)*w)}',f'offset_bottom = {n(psize[1]-y+ay*h)}',f'pivot_offset = {v(ax*w,(1-ay)*h)}']
   if sc is not None:props += [f'scale = {v(sc.get("ScaleX",1),sc.get("ScaleY",1))}']
   props+=[f'rotation = {n(float(e.get("RotationSkewX",0))*math.pi/180)}']
  if e.get('VisibleForFrame')=='False' or e.get('Visible')=='False':props+=['visible = false']
  alpha=float(e.get('Alpha',255))/255;props += [f'modulate = Color(1, 1, 1, {n(alpha)})',f'self_modulate = {rgba(e.find("CColor"))}',f'metadata/cocos_name = {q(original_name)}',f'metadata/cocos_tag = {int(e.get("Tag",0))}',f'metadata/action_tag = {int(e.get("ActionTag",0))}']
  if e.get('FlipX')=='True':props += ['scale = Vector2(-1, 1)']
  text=e.get('LabelText',e.get('LabelText',e.get('Text','')))
  if t=='TextureButton':
   if e.get('Scale9Enable')=='True':props += ['script = '+res('res://solitaire/newhd/cocos_button.gd','Script'),'scale9_margins = Vector4('+', '.join(n(e.get(k,0)) for k in ['LeftEage','RightEage','TopEage','BottomEage'])+')']
   for xml,prop in [('NormalFileData','texture_normal'),('PressedFileData','texture_pressed'),('DisabledFileData','texture_disabled')]:
    val=texture(e.find(xml))
    if val:props += [f'{prop} = {val}']
   props+=['ignore_texture_size = true','stretch_mode = 0']
  elif t in ['TextureRect','NinePatchRect']:
   props += [f'texture = {tx}']
   if t=='TextureRect':props += ['expand_mode = 1','stretch_mode = 0']
   else:
    for key,side in [('LeftEage','left'),('RightEage','right'),('TopEage','top'),('BottomEage','bottom')]:props += [f'patch_margin_{side} = {int(float(e.get(key,0)))}']
  elif t=='ColorRect':props += [f'color = {rgba(e.find("SingleColor"),float(e.get("BackColorAlpha",255))/255)}']
  elif t=='Label':
   font=res('res://assets/newhd/chinese.tres','Font');fd=e.find('LabelBMFontFile_CNB')
   if typ=='TextBMFontObjectData' and fd is not None and (A/fd.get('Path','')).is_file():font=res('res://assets/newhd/'+fd.get('Path'),'Font')
   props += ['script = '+res('res://solitaire/newhd/cocos_label.gd','Script'),f'design_size = {v(w,h)}',f'design_center = {v(x+(0.5-ax)*w,psize[1]-y+(ay-0.5)*h)}',f'design_font_size = {int(e.get("FontSize",32))}',f'bitmap_font = {str(typ=="TextBMFontObjectData").lower()}',f'fit_box = {str(e.get("IsCustomSize")=="True").lower()}',f'text = {q(text)}',f'theme_override_fonts/font = {font}',f'theme_override_font_sizes/font_size = {int(e.get("FontSize",32))}','horizontal_alignment = 1','vertical_alignment = 1','grow_horizontal = 2','grow_vertical = 2','clip_text = false']
   if e.get('OutlineEnabled')=='True':props += [f'theme_override_constants/outline_size = {int(e.get("OutlineSize",1))*2}',f'theme_override_colors/font_outline_color = {rgba(e.find("OutlineColor"))}']
  elif t=='TextureProgressBar':
   props += [f'value = {float(e.get("ProgressInfo",100))}','nine_patch_stretch = true']
   if tx:props+=['texture_progress = '+tx]
  elif typ=='TextAtlasObjectData':
   props += ['script = '+res('res://solitaire/native/atlas_number.gd','Script'),f'text = {q(text)}',f'glyph_size = {v(e.get("CharWidth",14),e.get("CharHeight",18))}',f'first_character = {q(e.get("StartChar","."))}']
   atlas=texture(e.find('LabelAtlasFileImage_CNB'))
   if atlas:props+=['atlas = '+atlas]
  if instance:props=[p for p in props if not p.startswith('layout_mode')]
  nodes.append((name,t,parent,props,instance));tags[e.get('ActionTag')]=(path,w,h,ax,ay,psize[1],typ)
  if typ=='ParticleObjectData':
   fd=e.find('FileData'); source=fd.get('Path','') if fd is not None else ''; pr=SC/'particles'/Path(source).with_suffix('.tscn')
   if pr.is_file():nodes.append(('Emitter','CPUParticles2D',path,[],res('res://'+str(pr.relative_to(P)),'PackedScene')))
   else:unsupported.append((str(rel),name,'particle'))
  children=e.find('Children')
  if t=='ScrollContainer':
   inner=e.find('InnerNodeSize');iw=float(inner.get('Width',w)) if inner is not None else w;ih=float(inner.get('Height',h)) if inner is not None else h
   nodes.append(('Content','Control',path,[f'custom_minimum_size = {v(iw,ih)}','layout_mode = 2','mouse_filter = 2'],None));path='Content' if path=='.' else path+'/Content';w,h=iw,ih
  for child in children if children is not None else []:visit(child,path,(w,h))
 visit(root,None,(1080,1920))
 anim=r.find('.//Animation');timelines=[]
 if anim is not None:
  for tl in anim.findall('Timeline'):
   tag=tl.get('ActionTag');prop=tl.get('Property')
   if tag not in tags:continue
   keys=sorted(list(tl),key=lambda k:int(k.get('FrameIndex',0)))
   if not keys:continue
   timelines.append((tags[tag],prop,keys))
 clips=r.findall('.//AnimationInfo')
 if not clips and anim is not None:clips=[E.Element('AnimationInfo',Name='default',StartIndex='0',EndIndex=anim.get('Duration','0'))]
 library={}
 def raw(k,prop):
  if prop in ['Position','RotationSkew']:return [float(k.get('X',0)),float(k.get('Y',0))]
  if prop=='Scale':return [float(k.get('X',k.get('ScaleX',1))),float(k.get('Y',k.get('ScaleY',1)))]
  if prop=='Alpha':return [float(k.get('Value',255))]
  if prop=='VisibleForFrame':return k.get('Value','True')=='True'
  if prop=='FileData':return texture(k.find('TextureFile')) or texture(k.find('FileData'))
  return k.attrib
 def at(keys,frame,prop):
  a=keys[0]
  for key in keys:
   if int(key.get('FrameIndex',0))<=frame:a=key
   else:break
  val=raw(a,prop)
  if prop not in ['Position','Scale','RotationSkew','Alpha'] or a.get('Tween')=='False':return val
  i=keys.index(a)
  if i==len(keys)-1 or frame<int(a.get('FrameIndex',0)):return val
  b=keys[i+1];f=(frame-int(a.get('FrameIndex',0)))/(int(b.get('FrameIndex',0))-int(a.get('FrameIndex',0)));ee=a.find('EasingData');f=easing(int(ee.get('Type',0)) if ee is not None else 0,f)
  return [av+(bv-av)*f for av,bv in zip(val,raw(b,prop))]
 for ci in clips:
  cname=ci.get('Name');start=int(ci.get('StartIndex',0));end=int(ci.get('EndIndex',start));sid='Anim_'+re.sub('[^a-zA-Z0-9_]','_',cname);library[cname]=sid
  lines=[f'[sub_resource type="Animation" id="{sid}"]',f'resource_name = {q(cname)}',f'length = {n(max(.001,(end-start)/60))}'];idx=0
  for info,prop,keys in timelines:
   path,w,h,ax,ay,ph,typ=info;path='' if path=='.' else path
   if prop not in ['Position','Scale','RotationSkew','Alpha','VisibleForFrame','FileData','ActionValue','FrameEvent']:unsupported.append((str(rel),prop));continue
   if prop in ['ActionValue','FrameEvent']:
    times=[];vals=[]
    for k in keys:
     fr=int(k.get('FrameIndex',0))
     if start<=fr<=end:
      times.append(n((fr-start)/60));vals.append('{"method": &"timeline_event", "args": ['+q(path)+','+q(prop)+','+q(json.dumps(k.attrib))+']}')
    if not times:continue
    lines += [f'tracks/{idx}/type = "method"',f'tracks/{idx}/path = NodePath(".")',f'tracks/{idx}/keys = {{"times": PackedFloat32Array({", ".join(times)}), "transitions": PackedFloat32Array({", ".join("1" for _ in times)}), "values": [{", ".join(vals)}]}}'];idx+=1;continue
   sampleframes=list(range(start,end+1));times=[];values=[];last=None
   for fr in sampleframes:
    val=at(keys,fr,prop)
    if prop=='Position':value=v(val[0]-ax*w,ph-val[1]-(1-ay)*h);pn='position'
    elif prop=='Scale':value=v(*val);pn='scale'
    elif prop=='RotationSkew':value=n(val[0]*math.pi/180);pn='rotation'
    elif prop=='Alpha':value='Color(1, 1, 1, '+n(val[0]/255)+')';pn='modulate'
    elif prop=='VisibleForFrame':value=str(val).lower();pn='visible'
    else:
     value=val;pn='texture'
     if not value:continue
    if value==last and fr!=end:continue
    times.append(n((fr-start)/60));values.append(value);last=value
   if not times:continue
   lines += [f'tracks/{idx}/type = "value"',f'tracks/{idx}/path = NodePath({q((path+":" if path else ":")+pn)})',f'tracks/{idx}/interp = {0 if prop in ["VisibleForFrame","FileData"] else 1}',f'tracks/{idx}/keys = {{"times": PackedFloat32Array({", ".join(times)}), "transitions": PackedFloat32Array({", ".join("1" for _ in times)}), "update": {1 if prop in ["VisibleForFrame","FileData"] else 0}, "values": [{", ".join(values)}]}}'];idx+=1
  subs += ['\n'.join(lines)];timeline_report[str(rel)+':'+cname]=idx
 if library:
  subs+=['[sub_resource type="AnimationLibrary" id="Library"]\n_data = {\n'+',\n'.join(q(k)+': SubResource('+q(val)+')' for k,val in library.items())+'\n}']
  nodes.append(('AnimationPlayer','AnimationPlayer','.', ['root_node = NodePath("..")','libraries = {&"": SubResource("Library")}','callback_mode_method = 1'],None))
 output=[f'[gd_scene load_steps={len(resources)+len(subs)+1} format=3]','']+[f'[ext_resource type={q(t)} path={q(p)} id={q(i)}]' for (p,t),i in resources.items()]+['']+subs
 for name,t,parent,props,instance in nodes:
  header=f'[node name={q(name)}'+(' type='+q(t) if not instance else '')+('' if parent is None else ' parent='+q(parent))+(' instance='+instance if instance else '')+']'
  output+=['',header,*props]
 target.write_text('\n'.join(output)+'\n');return count
if __name__=='__main__':
 assets();counts={str(f.relative_to(S/'cocosstudio')):import_scene(f) for f in sorted((S/'cocosstudio').rglob('*.csd'))}
 manifest={'source_ref':'origin/NewHD','source_commit':'cc2a21868d726d4ddaaace762c441c887028edd2','design':[1080,1920],'scenes':counts,'timelines':timeline_report,'missing':sorted(set(missing)),'unsupported':sorted(set(unsupported))}
 (A/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2));print('Scenes',len(counts),'Nodes',sum(x or 0 for x in counts.values()),'clips',len(timeline_report),'missing',len(set(missing)),'unsupported',len(set(unsupported)))

 # Finalize resources on every rebuild; standalone sprites are temporary only.
 from use_existing_atlases import main as use_atlases
 use_atlases()
