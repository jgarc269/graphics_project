#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color, color_r, color_i;

    vec3 r = ray.direction + 2 * dot(-ray.direction,normal) * normal;

    Ray n_ray {intersection_point, r.normalized()};
    
    color_r = world.Cast_Ray(n_ray, recursion_depth + 1);

    color_i = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

    color = reflectivity  * color_r + color_i * (1 - reflectivity);

    return color;
}
