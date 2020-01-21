#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit h;
    double a, b, c;
    a = dot(r.direction(), r.direction());
    b = 2.0 * r.diection * dot(endpoint - center);
    c = dot((endpoint - center),(endpoint - center)) - (radius * radius);
    
    double discrim = b*b - 4*a*c;
    
    if(discrim < 0)
    {
        // no intersection
        h.dist = 0;
        h.part = 0;
    }
    else
    {
        h.dist = (-b - sqrt(disrim) / (2.0 * a));
        h.part = 0;
    }
    
    
    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
