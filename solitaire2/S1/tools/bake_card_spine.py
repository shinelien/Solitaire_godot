"""Bake the supplied unweighted Spine 3.7 card rig into Godot AnimationLibrary.

This is an asset converter for THIS rig, not a general Spine runtime. Rejects
weighted meshes/constraints rather than silently approximating them. Original
Bezier curves, shear, vertex deformation, attachments and event times are
sampled at 120 Hz. Playback uses native AnimationPlayer + Polygon2D.
"""
from pathlib import Path
import json, math
from PIL import Image

ROOT=Path(__file__).resolve().parents[1]
ASSETS=ROOT/'assets/master/spine'
DATA=json.loads((ASSETS/'skeleton.json').read_text())
assert not any(DATA.get(k) for k in ['ik','transform','path']), 'Rig constraints need an explicit converter'
SKIN=DATA['skins']['default']
SLOTS=[s for s in DATA['slots'] if s['name'] not in ['poker0','poker2','poker3']]
def q(x): return json.dumps(x)
def fmt(x): return str(round(x,6))
def arr(x): return ', '.join(fmt(v) for v in x)
def color(x): return [int(x[i:i+2],16)/255 for i in range(0,8,2)]
def curve(a,x):
    c=a.get('curve')
    if c=='stepped': return 0
    if not isinstance(c,list): return x
    lo,hi=0.,1.
    for _ in range(24):
        t=(lo+hi)/2; u=1-t; bx=3*u*u*t*c[0]+3*u*t*t*c[2]+t*t*t
        if bx<x: lo=t
        else: hi=t
    t=(lo+hi)/2; u=1-t
    return 3*u*u*t*c[1]+3*u*t*t*c[3]+t*t*t
def sample(keys,t,fields,defaults,angle=False):
    if not keys or t<keys[0].get('time',0)-1e-9: return defaults[:]
    i=0
    while i+1<len(keys) and keys[i+1].get('time',0)<=t+1e-9: i+=1
    a=keys[i]; av=[a.get(k,defaults[j]) for j,k in enumerate(fields)]
    if i==len(keys)-1: return av
    b=keys[i+1]; f=curve(a,(t-a.get('time',0))/(b.get('time',0)-a.get('time',0)))
    out=[]
    for j,k in enumerate(fields):
        d=b.get(k,defaults[j])-av[j]
        if angle: d=(d+180)%360-180
        out.append(av[j]+f*d)
    return out
def attachment(slot,clip,t):
    name=slot.get('attachment'); keys=clip.get('slots',{}).get(slot['name'],{}).get('attachment',[])
    for k in keys:
        if k.get('time',0)<=t+1e-9: name=k.get('name')
    return name
def rgba(slot,clip,t):
    defaults=color(slot.get('color','ffffffff')); keys=clip.get('slots',{}).get(slot['name'],{}).get('color',[])
    converted=[dict(time=k.get('time',0),curve=k.get('curve'),**dict(zip('rgba',color(k['color'])))) for k in keys]
    return sample(converted,t,list('rgba'),defaults)
def pose(clip,t):
    world={}
    for b in DATA['bones']:
        ts=clip.get('bones',{}).get(b['name'],{})
        tx,ty=sample(ts.get('translate'),t,['x','y'],[0,0]); sx,sy=sample(ts.get('scale'),t,['x','y'],[1,1]); shx,shy=sample(ts.get('shear'),t,['x','y'],[0,0]); r=sample(ts.get('rotate'),t,['angle'],[0],True)[0]+b.get('rotation',0)
        sx*=b.get('scaleX',1); sy*=b.get('scaleY',1)
        rx=math.radians(r+b.get('shearX',0)+shx); ry=math.radians(r+90+b.get('shearY',0)+shy)
        a,c=math.cos(rx)*sx,math.sin(rx)*sx; bb,d=math.cos(ry)*sy,math.sin(ry)*sy; x,y=b.get('x',0)+tx,b.get('y',0)+ty
        if 'parent' in b:
            pa,pb,pc,pd,px,py=world[b['parent']]
            a,bb,c,d,x,y=pa*a+pb*c,pa*bb+pb*d,pc*a+pd*c,pc*bb+pd*d,pa*x+pb*y+px,pc*x+pd*y+py
        world[b['name']]=(a,bb,c,d,x,y)
    return world
def vertices(slot,name,clip,t,world):
    at=SKIN[slot['name']][name]
    if at.get('type')=='mesh':
        vs=at['vertices'][:]
        assert len(vs)==len(at['uvs']), 'Weighted mesh is unsupported'
        keys=clip.get('deform',{}).get('default',{}).get(slot['name'],{}).get(name,[])
        ds=[]
        for k in keys:
            k=dict(k); offset=k.get('offset',0); values=k.get('vertices',[])
            ds.append(dict(k,**{str(j): values[j-offset] if offset<=j<offset+len(values) else 0 for j in range(len(vs))}))
        deformation=sample(ds,t,[str(j) for j in range(len(vs))],[0]*len(vs))
        vs=[v+d for v,d in zip(vs,deformation)]
    else:
        w,h=at['width']/2,at['height']/2; r=math.radians(at.get('rotation',0)); co,si=math.cos(r),math.sin(r); sx,sy=at.get('scaleX',1),at.get('scaleY',1); vs=[]
        for x,y in [(-w,h),(w,h),(w,-h),(-w,-h)]:
            vs.extend([co*x*sx-si*y*sy+at.get('x',0),si*x*sx+co*y*sy+at.get('y',0)])
    a,b,c,d,x,y=world[slot['bone']]; out=[]
    for vx,vy in zip(vs[::2],vs[1::2]): out.extend([a*vx+b*vy+x,-(c*vx+d*vy+y)])
    return out
def duration(obj):
    if isinstance(obj,dict): return max([obj.get('time',0)]+[duration(v) for v in obj.values()])
    if isinstance(obj,list): return max([0]+[duration(v) for v in obj])
    return 0

def atlas_regions():
    sheet=Image.open(ASSETS/'skeleton.png'); regions={}; name=None; props={}
    def save():
        if not name or 'xy' not in props: return
        x,y=map(int,props['xy'].split(',')); w,h=map(int,props['size'].split(','))
        im=sheet.crop((x,y,x+(h if props.get('rotate')=='true' else w),y+(w if props.get('rotate')=='true' else h)))
        if props.get('rotate')=='true': im=im.transpose(Image.Transpose.ROTATE_90)
        im.save(ASSETS/(name+'.png')); regions[name]=im.size
    for line in (ASSETS/'skeleton.atlas').read_text().splitlines():
        if line and not line[0].isspace() and ':' not in line:
            save(); name=line.strip(); props={}
        elif ':' in line and line[0].isspace():
            k,v=line.strip().split(':',1); props[k]=v.strip()
    save(); return regions

def bake():
    regions=atlas_regions(); ext={}; sub=[]; library={}; bindings={}
    def tex(name):
        if name not in ext: ext[name]=str(len(ext)+1)
        return f'ExtResource("{ext[name]}")'
    for s in SLOTS:
        bindings[s['name']]={}
        for name,at in SKIN.get(s['name'],{}).items():
            path=at.get('path',name); assert path in regions,path
            w,h=regions[path]; uv=at.get('uvs',[0,0,1,0,1,1,0,1])
            bindings[s['name']][name]={'texture':'res://assets/master/spine/'+path+'.png','uv':[v*(w if i%2==0 else h) for i,v in enumerate(uv)],'triangles':at.get('triangles',[0,1,2,0,2,3]),'screen':s.get('blend')=='screen'}
    for name,clip in {'RESET':{},**DATA['animations']}.items():
        length=max(.001,duration(clip)); times=sorted(set([0,length]+[i/120 for i in range(1,math.ceil(length*120))]))
        sid='Animation_'+name; lines=[f'[sub_resource type="Animation" id="{sid}"]',f'resource_name = {q(name)}',f'length = {fmt(length)}']; track=0
        poses=[pose(clip,t) for t in times]
        for s in SLOTS:
            sn=s['name']; att=[attachment(s,clip,t) for t in times]
            names=set(att)-{None}
            if len(names)>1: raise ValueError(f'Attachment topology changes in {name}/{sn}: {names}')
            atname=next(iter(names),None)
            if atname is None:
                lines += [f'tracks/{track}/type = "value"',f'tracks/{track}/path = NodePath("{sn}:visible")',f'tracks/{track}/keys = {{"times": PackedFloat32Array(0), "transitions": PackedFloat32Array(1), "update": 1, "values": [false]}}']; track+=1
                continue
            polys=[f'PackedVector2Array({arr(vertices(s,atname,clip,t,p))})' for t,p in zip(times,poses)]
            colors=[f'Color({arr(rgba(s,clip,t))})' for t in times]
            values={'polygon':polys,'modulate':colors,'visible':['true' if a else 'false' for a in att]}
            if sn!='card_bg_1': values['texture']=[tex(SKIN[sn][atname].get('path',atname))]*len(times)
            for prop,vs in values.items():
                lines += [f'tracks/{track}/type = "value"',f'tracks/{track}/path = NodePath("{sn}:{prop}")',f'tracks/{track}/interp = 1',f'tracks/{track}/keys = {{"times": PackedFloat32Array({arr(times)}), "transitions": PackedFloat32Array({arr([1]*len(times))}), "update": {1 if prop in ["texture","visible"] else 0}, "values": [{", ".join(vs)}]}}']; track+=1
        events=clip.get('events',[])
        if events:
            lines += [f'tracks/{track}/type = "method"',f'tracks/{track}/path = NodePath("..")',f'tracks/{track}/keys = {{"times": PackedFloat32Array({arr([e["time"] for e in events])}), "transitions": PackedFloat32Array({arr([1]*len(events))}), "values": [{", ".join("{\"method\": &\"_spine_event\", \"args\": ["+q(e["name"])+"]}" for e in events)}]}}']
        sub.extend(lines+['']); library[name]=sid
    out=[f'[gd_resource type="AnimationLibrary" load_steps={len(ext)+len(library)+1} format=3]','']
    for n,i in ext.items(): out += [f'[ext_resource type="Texture2D" path="res://assets/master/spine/{n}.png" id="{i}"]']
    out += ['']+sub+['[resource]','_data = {',',\n'.join(f'&{q(n)}: SubResource("{s}")' for n,s in library.items()),'}']
    (ASSETS/'card_animations.tres').write_text('\n'.join(out)+'\n')
    (ASSETS/'bindings.json').write_text(json.dumps(bindings,separators=(',',':')))
    print('Baked',len(library)-1,'original Spine clips at 120 Hz, preserving mesh deformation and events')

if __name__=='__main__': bake()
