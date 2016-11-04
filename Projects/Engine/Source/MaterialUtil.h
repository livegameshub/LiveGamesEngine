#ifndef _MATERIAL_UTIL_H_
#define _MATERIAL_UTIL_H_

/* nodes */

#define UNIFORM_MODEL "u_model"
#define UNIFORM_NORMAL "u_normal"

/* camera */
#define UNIFORM_VIEW "u_view"
#define UNIFORM_PROJECTION "u_projection"

#define UNIFORM_CAMERA_POSITION "u_camera_position"

/* material */
#define UNIFORM_MATERIAL_DIFFUSE "u_material.diffuse"
#define UNIFORM_MATERIAL_SPECULAR "u_material.specular"
#define UNIFORM_MATERIAL_SHININESS "u_material.shininess"

/* lights */
#define UNIFORM_AMBIENT_LIGHT "u_ambient_light"

#define UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE "u_directional_light.light.diffuse"
#define UNIFORM_DIRECTIONAL_LIGHT_SPECULAR "u_directional_light.light.specular"
#define UNIFORM_DIRECTIONAL_LIGHT_DIRECTION "u_directional_light.direction"

/* default values */
#define MATERIAL_DEFAULT_DIFFUSE_COLOR vec3(1.0f)
#define MATERIAL_DEFAULT_SPECULAR_COLOR vec3(0.5f)
#define MATERIAL_DEFAULT_SHININESS 32.0f

#endif // _MATERIAL_UTIL_H_
