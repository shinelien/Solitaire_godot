"""Cocos plist particle parameters -> native CPU particle resources.
The distributions differ between engines; motion parameters and source textures
are preserved. Radial emitters remain an explicit conversion gap in manifest.
"""
from pathlib import Path
import plistlib,base64,zlib,json,io
from PIL import Image
P=Path(__file__).resolve().parents[1];A=P/'assets/newhd';O=P/'scenes/newhd/particles';O.mkdir(parents=True,exist_ok=True)
def num(x):return str(round(float(x),6))
def q(x):return json.dumps(x)
def color(d,pre):return ', '.join(num(d.get(pre+'Color'+key,1)) for key in ['Red','Green','Blue','Alpha'])
REPORT=[]
for f in sorted(A.rglob('*.plist')):
 try:d=plistlib.loads(f.read_bytes());life=float(d['particleLifespan'])
 except (KeyError,ValueError):continue
 name=d.get('textureFileName','');texture=f.parent/name
 if not texture.exists():texture=f.parent/Path(name.replace('\\','/')).name
 if 'textureImageData' in d and (not texture.exists() or texture.parent.name=='particle_textures'):
  raw=base64.b64decode(d['textureImageData'])
  try:raw=zlib.decompress(raw,zlib.MAX_WBITS|32)
  except zlib.error:pass
  texture=A/'particle_textures'/(f.stem+'.png');texture.parent.mkdir(exist_ok=True)
  Image.open(io.BytesIO(raw)).convert('RGBA').save(texture,format='PNG')
 if not texture.exists():REPORT.append([str(f.relative_to(A)),'missing particle texture',name]);continue
 if int(d.get('emitterType',0))!=0:REPORT.append([str(f.relative_to(A)),'radial emitter'])
 w=Image.open(texture).width
 lv=float(d.get('particleLifespanVariance',0));size=float(d.get('startParticleSize',16));szv=float(d.get('startParticleSizeVariance',0));end=float(d.get('finishParticleSize',size));end=size if end<0 else end
 out=['[gd_scene load_steps=6 format=3]',f'[ext_resource type="Texture2D" path={q("res://"+str(texture.relative_to(P)))} id="1"]','[sub_resource type="Gradient" id="Color"]',f'colors = PackedColorArray({color(d,"start")}, {color(d,"finish")})','[sub_resource type="Curve" id="Size"]',f'_data = [Vector2(0, 1), 0.0, 0.0, 0, 0, Vector2(1, {num(end/max(.01,size))}), 0.0, 0.0, 0, 0]','[sub_resource type="Curve" id="Rotation"]',f'_data = [Vector2(0, {num(float(d.get("rotationStart",0))/360)}), 0.0, 0.0, 0, 0, Vector2(1, {num(float(d.get("rotationEnd",0))/360)}), 0.0, 0.0, 0, 0]','[sub_resource type="CanvasItemMaterial" id="Blend"]',f'blend_mode = {1 if float(d.get("blendFuncDestination",771))==1 else 0}','[node name="Particles" type="CPUParticles2D"]','material = SubResource("Blend")',f'amount = {max(1,int(d.get("maxParticles",20)))}',f'lifetime = {num(max(.1,life+lv))}',f'lifetime_randomness = {num(min(1,2*lv/max(.1,life+lv)))}','texture = ExtResource("1")','emission_shape = 3',f'emission_rect_extents = Vector2({num(d.get("sourcePositionVariancex",0))}, {num(d.get("sourcePositionVariancey",0))})',f'direction = Vector2({num(__import__("math").cos(float(d.get("angle",0))*__import__("math").pi/180))}, {num(-__import__("math").sin(float(d.get("angle",0))*__import__("math").pi/180))})',f'spread = {num(d.get("angleVariance",0))}',f'gravity = Vector2({num(d.get("gravityx",0))}, {num(-float(d.get("gravityy",0)))})',f'initial_velocity_min = {num(max(0,float(d.get("speed",0))-float(d.get("speedVariance",0))))}',f'initial_velocity_max = {num(max(0,float(d.get("speed",0))+float(d.get("speedVariance",0))))}',f'radial_accel_min = {num(float(d.get("radialAcceleration",0))-float(d.get("radialAccelVariance",0)))}',f'radial_accel_max = {num(float(d.get("radialAcceleration",0))+float(d.get("radialAccelVariance",0)))}',f'tangential_accel_min = {num(float(d.get("tangentialAcceleration",0))-float(d.get("tangentialAccelVariance",0)))}',f'tangential_accel_max = {num(float(d.get("tangentialAcceleration",0))+float(d.get("tangentialAccelVariance",0)))}',f'scale_amount_min = {num(max(0,size-szv)/w)}',f'scale_amount_max = {num((size+szv)/w)}','scale_amount_curve = SubResource("Size")','color_ramp = SubResource("Color")','angle_min = 0.0','angle_max = 360.0','angle_curve = SubResource("Rotation")',f'local_coords = {str(int(d.get("positionType",0))==2).lower()}',f'one_shot = {str(float(d.get("duration",-1))>=0).lower()}']
 rel=f.relative_to(A).with_suffix('.tscn');target=O/rel;target.parent.mkdir(parents=True,exist_ok=True);target.write_text('\n'.join(out)+'\n')
(A/'particle_conversion.json').write_text(json.dumps(REPORT,ensure_ascii=False,indent=2));print('Particle scenes',len(list(O.rglob('*.tscn'))),'gaps',len(REPORT))
