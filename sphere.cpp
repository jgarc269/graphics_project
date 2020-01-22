#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit h;
    double a = 0;
    double b = 0;
    double c = 0;
    a = dot(ray.direction, ray.direction);
    b = 2.0 * dot(ray.direction,(ray.endpoint - center));
    c = dot((ray.endpoint - center),(ray.endpoint - center)) - (radius * radius);
    
    double discrim = b*b - 4*a*c;
    
    if(discrim < 0)
    {
        // no intersection
        h.dist = 0;
        h.part = 0;
	h.object = this;
    }
    else if(discrim == 0)
    {
	h.dist = -b;
	h.part = 0;
	h.object = this;
    }
    else
    {
     	double t1 = (-b + sqrt(discrim) / (2.0 * a));
	double t2 = (-b - sqrt(discrim) / (2.0 * a));
	
	if(t1 < 0 && t2 < 0)
	{
	    h.dist = 0;
	    h.part = 0;
	    h.object = this;
	}
	else if (t1 > 0)
	{
	    h.dist = t2;
	    h.part = 0;
	    h.object = this;
	}
	else if(t2 > 0)
	{
	    h.dist = t1;
	    h.part = 0;
	    h.object = this;
	}
	else if(t1 > t2)
	{
	    h.dist = t2;
            h.part = 0;
	    h.object = this;
	}
	else if(t1 < t2)
	{
	    h.dist = t1;
	    h.part = 0;
	    h.object = this;
	}
	else
	{
	    h.dist = t2;
	    h.part = 0;
	    h.object = this;
	}
    }
    
    return h;
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
