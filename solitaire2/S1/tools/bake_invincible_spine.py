"""Sample rigs with the ORIGINAL Cocos Spine evaluator (weighted meshes + constraints).
Native Godot Polygon2D actors play the sampled geometry via AnimationPlayer.
No Cocos or Spine runtime is linked into the Godot product.
"""
from pathlib import Path
import json,subprocess,gzip
P=Path(__file__).resolve().parents[1];A=P/'assets/invincible';O=A/'baked';O.mkdir(exist_ok=True)
SKINS={4:'douyu1',5:'douyu2',6:'douyu3',7:'taiyangyu',8:'tiaowenyu',9:'hudieyu1',10:'hudieyu2',11:'xipanyu',12:'diaoyu',13:'wuguoyu',14:'shayu'}
def bake(name,skeleton,atlas,skin='default',fps=60):
 raw=subprocess.check_output([str(P/'tools/spine_sampler'),str(A/skeleton),str(A/atlas),skin,str(fps)])
 d=json.loads(raw);d['atlas_dir']='res://assets/invincible/'+str(Path(atlas).parent)
 source=json.loads((A/skeleton).read_text());d['events']={clip:data.get('events',[]) for clip,data in source['animations'].items()}
 attachments=[]; ids={}
 for clip in d['clips'].values():
  compact=[]
  for frame in clip['frames']:
   row=[]
   for item in frame:
    key=(item['slot'],item['name'],item['page'])
    if key not in ids:
     ids[key]=len(attachments);attachments.append({k:v for k,v in item.items() if k not in ['vertices','color']})
    row.append([ids[key],item['vertices'],item['color']])
   compact.append(row)
  clip['frames']=compact
 d['attachments']=attachments
 if name=='card':
  for a in attachments:
   at=source['skins']['default'][a['slot']][a['name']]
   if a['slot'] in ['card_bg_1','poker0','poker2','poker3']:
    # computeWorldVertices returns BR, BL, UL, UR, unlike the offset array.
    a['override_uv']=at.get('uvs',[1,1,0,1,0,0,1,0])
 (O/(name+'.json.gz')).write_bytes(gzip.compress(json.dumps(d,separators=(',',':')).encode(),compresslevel=9,mtime=0))
 print(name, len(raw), 'bytes',len(d['clips']),'clips')
if __name__=='__main__':
 bake('card','res/pk/skeleton.json','res/pk/skeleton.atlas',fps=120)
 for i in range(25):
  group='4-5-6' if i in [4,5,6] else '7-8' if i in [7,8] else '9-10' if i in [9,10] else '12-13' if i in [12,13] else str(i)
  bake('fish'+str(i),'res/fish/fish'+group+'/skeleton.json','res/fish18_shark.atlas',SKINS.get(i,'default'))
