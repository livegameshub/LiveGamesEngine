
attribute vec3 a_position;
attribute vec3 a_normal;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat3 u_normal;

varying vec3 v_position;
varying vec3 v_normal;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
	
	v_position = vec3(u_model * vec4(a_position, 1.0));
	
	v_normal = u_normal * a_normal;
}
