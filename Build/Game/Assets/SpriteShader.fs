
struct Material
{
	vec3 diffuse;
};

uniform Material u_material;
uniform sampler2D u_diffuse_sampler;

varying vec2 v_uv;

void main()
{
	gl_FragColor =  vec4(u_material.diffuse, 1.0) * texture2D(u_diffuse_sampler, v_uv.xy);
}