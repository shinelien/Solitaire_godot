# Legacy asset provenance manifest (WP-08)

- Source (read-only, immutable Git object): `WTF-Solitaire@InvincibleWarrior@74f51802c8a5356223c84d8aff81c3300f190a43`
- Extraction: `git show <object>:<path>` (no checkout of either old repo), then `shasum -a 256` of the exported bytes.
- Exported files are byte-identical to the fixed Git blob content; each row lists the source path inside the fixed object, the Git blob sha (from `git rev-parse <object>:<path>`), exported size in bytes, and SHA-256 of the exported bytes.

| exported path | fixed source path | git blob sha (12+ shown) | bytes | sha256 (exported) |
|---|---|---|---|---|
| images/car_new_0_6.png | Resources/game/car_new_0_6.png | 34f2c737db508b7304899e9c4ad5d10c4a313118 | 652247 | 1260aa2bce0e40c6d2099b81ee91c882d60356f6aac089e2077b5c27cf0fff85 |
| images/car_new_0_6.atlas | Resources/game/car_new_0_6.atlas | a2c0aabd12bec4b759921997d9f92ae17324468a | 11125 | 633952a8a78c74e053ef709b43f7ffeaf50c4b62db127c689c5df94e44d0130a |
| images/car_new_0_1.png | Resources/game/car_new_0_1.png | 1d080ad75c62867d04e2365defe5651059935853 | 589435 | 90ebafeaa6c5ec0b5aa50fd1c03cd98f4e56703baa787c775ba9b8bda9059e5c |
| images/car_new_0_1.atlas | Resources/game/car_new_0_1.atlas | 1612f965c62f7a7924a4310ae2ecaef51cd53387 | 6389 | 95d6cfb422ea8e7aa5b935a05c865d3008c73d91467c3e447239fbb8b9baffa1 |
| images/background-0.png | Resources/background-0.png | c47b1a646bea70b127d66cea37ce3139f60bcfbf | 64100 | bba89241c9e73e90a32cc4090bfa6716a3addda7cff2975e6f8ede31778664d0 |
| audio/deal.mp3 | Resources/music/deal.mp3 | 28363a57f65d (see note) | 52701 | 4082f13182865e7672b2923fc694f5246824c3243b1174a0f1a32481d17486c0 |
| audio/movecard.mp3 | Resources/music/movecard.mp3 | 789293dbec1a (see note) | 10652 | 2a465c43ed4d8cc0dde71d42ebb568cb2e9ee396abb194dbf90912764e0430e2 |
| audio/nomove.mp3 | Resources/music/nomove.mp3 | 9ef2f5d415af (see note) | 1965 | 9eebca0da25a5bca77ade9825964484c37661329fb159167ded1f2cfb73f2268 |
| audio/undo.mp3 | Resources/music/undo.mp3 | 5fbfae62f19f (see note) | 15261 | 635c27eae1cbebe241519763aef309ec3a38ef84e1cfbfe6d7d86b6d7ecb450c |
| audio/auto.mp3 | Resources/music/auto.mp3 | 35a807fb1670 (see note) | 27286 | 7d952b946ff4e610444e13362d49311174bac7df11a6017ebc3d8be2dcf72d16 |
| audio/autoplay.mp3 | Resources/music/autoplay.mp3 | 576ea7fabf43 (see note) | 249499 | 67bc858bb22b0e3c82bf251ec0ab96dcf28d6ada88ce093d1e2c00c4796edecb |
| audio/victory.mp3 | Resources/music/victory.mp3 | 03ca21b27753 (see note) | 196478 | 242efd6da27ee91129f7524c5223c483f28b9ba791902619ded7cddb30409668 |

Full audio blob ids (from `git rev-parse <object>:Resources/music/X.mp3`): deal `28363a57f65d114dc764b259f221cb2d900c068d`; movecard `789293dbec1aaa97a680b0a69a68f2ac6938032a`; nomove `9ef2f5d415afafcf4405adb4518470ae9bc8a77e`; undo `5fbfae62f19fcd1151e811fd7f549fc2b7680736`; auto `35a807fb1670360780fce5dc0b052a7799bb41ac`; autoplay `576ea7fabf4307e0a3d0551af7e755e3518fb09d`; victory `03ca21b27753d7852c87316230b3d4bd80659ce1`. `deal.mp3` and `shuffle.mp3` share the same blob, so only `deal.mp3` is exported.

Usage: images are loaded at runtime through `LegacyAtlas` (presentation infrastructure only) which parses the Spine text `.atlas` files and exposes `AtlasTexture` regions. Audio is streamed through `AudioStreamPlayer` nodes. Nothing under `assets/legacy` is used by core/deal/application code.
