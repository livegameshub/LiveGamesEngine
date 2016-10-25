
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_uv;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat3 u_normal;

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_uv;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
	
	v_position = vec3(u_model * vec4(a_position, 1.0));
	
	v_normal = u_normal * a_normal;
	
	v_uv = vec2(a_uv.x, 1.0 - a_uv.y);
}
