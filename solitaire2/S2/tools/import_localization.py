import re,json
from pathlib import Path
base=Path(__file__).resolve().parents[2]
entries={}
for p in (base/'reference/NewHD/Classes').rglob('*.cpp'):
 s=re.sub(r'//[^\n]*','',p.read_text(errors='replace'))
 csd=re.search(r'BaseLayer\("([^"]+)\.csb"',s)
 if not csd:continue
 mapping={}
 for match in re.finditer(r'getNode\s*<[^;\n]+?>\s*\("([^"]+)"\)->setString\((?:Lang|UIUtils::getStringByName)\("([^"]+)"\)\)',s):mapping[match[1]]=match[2]
 vars={m[1]:m[2] for m in re.finditer(r'(\w+)\s*=\s*(?:this->)?getNode\s*<[^;\n]+?>\s*\("([^"]+)"\)',s)}
 for m in re.finditer(r'(\w+)->setString\((?:Lang|UIUtils::getStringByName)\("([^"]+)"\)\)',s):
  if m[1] in vars:mapping[vars[m[1]]]=m[2]
 for m in re.finditer(r'FIND_NODE\([^\n]+?,\s*[^\n]+?,\s*"([^"]+)"\)->setString\((?:Lang|UIUtils::getStringByName)\("([^"]+)"\)\)',s):mapping[m[1]]=m[2]
 if mapping:entries[csd[1]]=mapping
(base/'S2/assets/newhd/localization_bindings.json').write_text(json.dumps(entries,ensure_ascii=False,indent=2))
print('localized source bindings',len(entries),sum(map(len,entries.values())))
