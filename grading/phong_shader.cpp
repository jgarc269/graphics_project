#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;

    vec3 a_color = this->color_ambient * world.ambient_color * world.ambient_intensity;
     color = color + a_color;

    for(unsigned int i = 0; i < world.lights.size(); i++) 
    {
        vec3 li = world.lights[i]->position - intersection_point;

        vec3 d_color = d_color + this->color_diffuse * world.lights[i]->Emitted_Light(li) * std::max(dot(normal, li.normalized()), 0.0);

	vec3 r = -li + 2 * dot(li,normal) * normal;

	vec3 s_color = s_color + this->color_specular * world.lights[i]->Emitted_Light(li) * std::pow(std::max(dot(-ray.direction, r.normalized()), 0.0), specular_power);

	color = color + d_color + s_color;
    }
    return color;

}
