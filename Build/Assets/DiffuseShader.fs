
struct Material
{
	vec3 diffuse;
};

uniform Material u_material;

void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);//vec4(u_material.diffuse, 1.0);
}
