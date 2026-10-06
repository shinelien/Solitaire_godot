shader_type canvas_item;
uniform vec4 atlas_bounds;
void fragment() {
 vec2 edge = atlas_bounds.xy + atlas_bounds.zw;
 if (UV.x < atlas_bounds.x || UV.y < atlas_bounds.y || UV.x > edge.x || UV.y > edge.y) { COLOR = vec4(0.0); }
 else { COLOR *= texture(TEXTURE, clamp(UV, atlas_bounds.xy + TEXTURE_PIXEL_SIZE * 0.5, edge - TEXTURE_PIXEL_SIZE * 0.5)); }
}
