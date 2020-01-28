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
   // TODO; //determine the color
    
    for(unsigned int i = 0; i < world.lights.size(); i++) 
    {
        vec3 l = world.lights[i]->position - intersection_point;
        color = color + this->color_diffuse * world.lights[i]->Emitted_Light(l) * std::max(dot(normal, l.normalized()), 0.0);
    }
    return color;

}
