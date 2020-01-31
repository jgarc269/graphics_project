#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit h;
    double b = 2.0 * dot(ray.direction,(ray.endpoint - center));
    double c = dot((ray.endpoint - center),(ray.endpoint - center)) - (radius * radius);
    
    double discrim = b*b - 4*c;
    
    if(discrim <= 0)
    {
        // no intersection
        h.dist = 0;
        h.part = 0;
	    h.object = NULL;

		return h;
    }

    double t1 = (-b + sqrt(discrim)) / 2.0;
    double t2 = (-b - sqrt(discrim)) / 2.0;
	
	if(t1 < 0 && t2 < 0)
	{
	    h.dist = 0;
	    h.part = part;
	    h.object = NULL;
	}
	else if (t1 < 0)
	{
	    h.dist = t2;
	    h.part = part;
	    h.object = this;
	}
	else if(t2 < 0)
	{
	    h.dist = t1;
	    h.part = part;
	    h.object = this;
	}
	else if(t1 > t2)
	{
	    h.dist = t2;
        h.part = part;
	    h.object = this;
	}
	else if(t1 < t2)
	{
	    h.dist = t1;
	    h.part = part;
	    h.object = this;
	}
	else
	{
	    h.dist = t2;
	    h.part = part;
	    h.object = this;
	}
    
    return h;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = (point - center) / radius;
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
