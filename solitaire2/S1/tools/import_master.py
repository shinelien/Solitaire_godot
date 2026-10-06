"""Reproducible Cocos master assets/CSD -> native Godot scenes.

Run with Python + Pillow. Never writes to the Cocos checkout. The only assets
from InvincibleWarrior are the explicitly requested Spine card animation.
"""
from pathlib import Path
import argparse, hashlib, json, plistlib, re, shutil, subprocess
import xml.etree.ElementTree as ET
from PIL import Image

PROJECT = Path(__file__).resolve().parents[1]
SOURCE = PROJECT.parents[2] / 'WTF-Solitaire'
OUT = PROJECT / 'assets/master'
SPINE_COMMIT = '74f51802c8a5356223c84d8aff81c3300f190a43'

def numbers(s): return [float(x) for x in re.findall(r'-?\d+(?:\.\d+)?', s)]
def q(s): return json.dumps(s, ensure_ascii=False)
def num(n): return f'{float(n):.6f}'
def v(x,y): return f'Vector2({num(x)}, {num(y)})'
def col(e, alpha=1):
    a = e.attrib if e is not None else {}
    return 'Color(%s)' % ', '.join(num(float(a.get(k,255))/255 * (alpha if k=='A' else 1)) for k in ['R','G','B','A'])

def import_assets():
    OUT.mkdir(parents=True, exist_ok=True)
    for folder in ['img','game','effect','music','Default','data']:
        shutil.copytree(SOURCE/'Resources'/folder, OUT/folder, dirs_exist_ok=True)
    for p in (SOURCE/'cocosstudio').rglob('*.png'):
        relative=p.relative_to(SOURCE/'cocosstudio'); target=OUT/relative
        if not target.exists():
            target.parent.mkdir(parents=True,exist_ok=True); shutil.copyfile(p,target)
    frames = OUT/'frames'; frames.mkdir(exist_ok=True)
    for p in sorted((OUT/'game').glob('*.plist')):
        data=plistlib.loads(p.read_bytes())
        sheet=Image.open(p.with_suffix('.png')).convert('RGBA')
        for name, f in data['frames'].items():
            x,y,w,h=map(int,numbers(f['frame']))
            if f.get('rotated'):
                im=sheet.crop((x,y,x+h,y+w)).transpose(Image.Transpose.ROTATE_90)
            else: im=sheet.crop((x,y,x+w,y+h))
            sw,sh=map(int,numbers(f['sourceSize']))
            sx,sy,cw,ch=map(int,numbers(f['sourceColorRect']))
            full=Image.new('RGBA',(sw,sh)); full.paste(im,(sx,sy)); full.save(frames/name)
    spine=OUT/'spine'; spine.mkdir(exist_ok=True)
    for name in ['skeleton.json','skeleton.atlas','skeleton.png']:
        raw=subprocess.check_output(['git','-C',str(SOURCE),'show',f'{SPINE_COMMIT}:Resources/res/pk/{name}'])
        (spine/name).write_bytes(raw)
    # Native Chinese font resource bundled with the project, no system path at runtime.
    (OUT/'chinese.tres').write_text('[gd_resource type="SystemFont" format=3]\n[resource]\nfont_names = PackedStringArray("PingFang SC", "Heiti SC", "Microsoft YaHei", "Noto Sans CJK SC")\n')

def localized(scene):
    strings=json.loads((OUT/'data/strings_zh.json').read_text())
    strings.update({'100068':'商店','100071':'设置','100072':'暂停','100073':'恭喜！'})
    cpp_path=SOURCE/'Classes/scene'/f'{scene}.cpp'
    if scene=='ItemNode': cpp_path=SOURCE/'Classes/scene/ShopNode.cpp'
    cpp=cpp_path.read_text(errors='replace') if cpp_path.exists() else ''
    return {name:strings.get(key,key) for name,key in re.findall(r'FIND_NODE\([^;]*?,\s*"([^"]+)"\)->setString\(UIUtils::getStringByName\("([^"]+)"\)\)',cpp)}

def import_scene(path):
    scene=path.stem; root=ET.parse(path).find('.//ObjectData'); loc=localized(scene)
    resources={}; nodes=[]
    def res(path,typ='Texture2D'):
        key=(path,typ)
        if key not in resources: resources[key]=str(len(resources)+1)
        return f'ExtResource("{resources[key]}")'
    def texture(e):
        if e is None: return None
        path=e.get('Path','')
        if not path: return None
        target=OUT/path
        if e.get('Type')=='PlistSubImage' or not target.exists(): target=OUT/'frames'/Path(path).name
        if not target.exists(): raise ValueError(f'Missing CSD texture {scene}: {path}')
        return res('res://'+str(target.relative_to(PROJECT)))
    def visit(e,parent,psize):
        name=e.get('Name','Layer').replace('/','_'); size=e.find('Size'); pos=e.find('Position'); anchor=e.find('AnchorPoint'); scale=e.find('Scale')
        w=float(size.get('X',0)) if size is not None else 0; h=float(size.get('Y',0)) if size is not None else 0
        x=float(pos.get('X',0)) if pos is not None else 0; y=float(pos.get('Y',0)) if pos is not None else 0
        ax=float(anchor.get('ScaleX',0)) if anchor is not None else 0; ay=float(anchor.get('ScaleY',0)) if anchor is not None else 0
        typ=e.get('ctype',''); tx=texture(e.find('FileData'))
        if 'Button' in typ: node_type='TextureButton'
        elif typ=='TextObjectData': node_type='Label'
        elif typ=='TextAtlasObjectData': node_type='Control'
        elif typ=='ScrollViewObjectData': node_type='ScrollContainer'
        elif tx: node_type='NinePatchRect' if e.get('Scale9Enable')=='True' else 'TextureRect'
        elif int(e.get('ComboBoxIndex',0))==1: node_type='ColorRect'
        else: node_type='Control'
        props=['layout_mode = 0']
        if parent is None:
            props+=['mouse_filter = 2',f'offset_right = {num(w)}',f'offset_bottom = {num(h)}']
        else:
            props += [f'offset_left = {num(x-ax*w)}',f'offset_top = {num(psize[1]-y-(1-ay)*h)}',f'offset_right = {num(x+(1-ax)*w)}',f'offset_bottom = {num(psize[1]-y+ay*h)}',f'pivot_offset = {v(ax*w,(1-ay)*h)}']
            props += [f'mouse_filter = {0 if node_type in ["TextureButton","ScrollContainer"] or e.get("TouchEnable")=="True" else 2}']
            if scale is not None: props += [f'scale = {v(scale.get("ScaleX",1),scale.get("ScaleY",1))}']
            if float(e.get('RotationSkewX',0)): props += [f'rotation = {num(float(e.get("RotationSkewX"))*3.141592653589793/180)}']
            if e.get('VisibleForFrame')=='False' or e.get('Visible')=='False': props+=['visible = false']
        props += [f'self_modulate = {col(e.find("CColor"))}']
        text=loc.get(name,e.get('LabelText',''))
        if node_type=='TextureButton':
            for xml,prop in [('NormalFileData','texture_normal'),('PressedFileData','texture_pressed'),('DisabledFileData','texture_disabled')]:
                t=texture(e.find(xml))
                if t: props += [f'{prop} = {t}']
            props += ['ignore_texture_size = true','stretch_mode = 0']
        elif node_type in ['TextureRect','NinePatchRect']:
            props += [f'texture = {tx}']
            if node_type=='TextureRect': props += ['expand_mode = 1','stretch_mode = 0']
            else:
                for k,n in [('LeftEage','left'),('RightEage','right'),('TopEage','top'),('BottomEage','bottom')]: props += [f'patch_margin_{n} = {int(float(e.get(k,0)))}']
        elif node_type=='ColorRect': props += [f'color = {col(e.find("SingleColor"),float(e.get("BackColorAlpha",255))/255)}']
        elif node_type=='Label':
            props += [f'text = {q(text)}',f'theme_override_fonts/font = {res("res://assets/master/chinese.tres","Font")}',f'theme_override_font_sizes/font_size = {int(e.get("FontSize",20))}','horizontal_alignment = 1','vertical_alignment = 1']
            if name=='text_rule': props += ['autowrap_mode = 3']
        elif typ=='TextAtlasObjectData':
            props += [f'script = {res("res://solitaire/native/atlas_number.gd","Script")}',f'text = {q(text)}',f'glyph_size = {v(e.get("CharWidth",14),e.get("CharHeight",18))}',f'first_character = {q(e.get("StartChar","."))}']
            atlas=texture(e.find('LabelAtlasFileImage_CNB'))
            if atlas: props += [f'atlas = {atlas}']
        if node_type=='ScrollContainer': props += ['horizontal_scroll_mode = 2' if e.get('ScrollDirectionType')=='Horizontal' else 'horizontal_scroll_mode = 0','vertical_scroll_mode = 0' if e.get('ScrollDirectionType')=='Horizontal' else 'vertical_scroll_mode = 2']
        nodes.append((name,node_type,parent,props))
        current=name if parent is None else (name if parent=='.' else parent+'/'+name)
        children=e.find('Children')
        if children is not None or node_type=='ScrollContainer':
            if node_type=='ScrollContainer':
                inner=e.find('InnerNodeSize'); iw=float(inner.get('Width',w)) if inner is not None else w; ih=float(inner.get('Height',h)) if inner is not None else h
                nodes.append(('Content','Control',current,[f'custom_minimum_size = {v(iw,ih)}','layout_mode = 2','mouse_filter = 2']))
                current += '/Content'; w,h=iw,ih
            for child in (children if children is not None else []): visit(child,'.' if parent is None else current,(w,h))
    visit(root,None,(576,1024))
    output=['[gd_scene load_steps=%d format=3]'%(len(resources)+1),'']
    for (p,t),i in resources.items(): output += [f'[ext_resource type="{t}" path={q(p)} id="{i}"]']
    for n,t,p,props in nodes:
        output += ['',f'[node name={q(n)} type={q(t)}'+(']' if p is None else f' parent={q(p)}]'),*props]
    target=PROJECT/'scenes/native'/f'{scene}.tscn'; target.write_text('\n'.join(output)+'\n')
    return len(nodes)

if __name__=='__main__':
    import_assets()
    counts={p.stem:import_scene(p) for p in sorted((SOURCE/'cocosstudio/ui').glob('*.csd'))}
    manifest={'master_commit':subprocess.check_output(['git','-C',str(SOURCE),'rev-parse','HEAD']).decode().strip(),'spine_commit':SPINE_COMMIT,'scenes':counts,'files':{str(p.relative_to(OUT)):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(OUT.rglob('*')) if p.is_file() and not p.name.endswith('.import')}}
    (OUT/'manifest.json').write_text(json.dumps(manifest,indent=2,ensure_ascii=False)+'\n')
    print('Imported master scenes:',counts)

    from use_master_atlases import main as use_atlases
    use_atlases()
