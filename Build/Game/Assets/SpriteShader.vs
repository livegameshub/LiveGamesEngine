
attribute vec2 a_position;
attribute vec2 a_uv;

uniform mat4 u_model;
uniform mat4 u_projection;

varying vec2 v_uv;

void main()
{
	gl_Position = u_projection * u_model * vec4(a_position, 0.0, 1.0);
	
	v_uv = vec2(a_uv.x, 1.0 - a_uv.y);
}