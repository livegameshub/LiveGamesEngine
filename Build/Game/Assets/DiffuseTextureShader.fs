
struct Light
{
	vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight
{
	vec3 direction;
	
	Light light;
};

struct Material
{
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

uniform Material u_material;
uniform DirectionalLight u_directional_light;

uniform vec3 u_camera_position;
uniform vec3 u_ambient_light;

uniform sampler2D u_diffuse_sampler;

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_uv;

vec3 calculateDirectionalLight(vec3 view_direction, vec3 normal, vec3 diffuse_color)
{
	// process the ambient light
	vec3 result = u_ambient_light * diffuse_color;

	// process the diffuse light
	vec3 light_direction = normalize(-u_directional_light.direction);
    float diffuse_factor = max(dot(normal, light_direction), 0.0);

	if (diffuse_factor > 0.0)
	{
		result += u_directional_light.light.diffuse * diffuse_color * diffuse_factor;
		
		// process the specular light
		vec3 reflect_direction = reflect(-light_direction, normal);
		float specular_factor = max(dot(view_direction, reflect_direction), 0.0);
		
		if (specular_factor > 0.0)
		{
			specular_factor = pow(specular_factor, u_material.shininess);
			
			result += u_directional_light.light.specular * u_material.specular * specular_factor;
		}
	}
	
    return result;
}

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 view_direction = normalize(u_camera_position - v_position);
	
	// calculate the diffuse color
	vec3 diffuse_color = u_material.diffuse *  vec3(texture2D(u_diffuse_sampler, v_uv.xy));
	vec3 color = calculateDirectionalLight(view_direction, normal, diffuse_color);

	gl_FragColor = vec4(color, 1.0);
}
