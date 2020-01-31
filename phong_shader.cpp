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
    for(unsigned int i = 0; i < world.lights.size(); i++) 
    {
        vec3 temp = world.lights[i]->position - intersection_point;
        color = color + this->color_diffuse * world.lights[i]->Emitted_Light(temp) * std::max(dot(normal, temp.normalized()), 0.0);
        color = color + color_ambient + color_diffuse + color_specular;
    }
    return color;

}
