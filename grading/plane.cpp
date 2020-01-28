#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit h = {NULL, 0, part};
    double t = 0; 

    if(dot(ray.direction, normal) == 0)
    {
	     h.dist = 0;
         h.object = NULL;
         h.part = part;
    }
    else
    {
    	t = dot((x1 - ray.endpoint), normal) / dot(ray.direction, normal);
	
        if(t > small_t)
        {
            h.dist = t;
            h.object = this;
            h.part = part;
        }
        else
        {
            h.dist = 0;
            h.object = NULL;
            h.part = part;
        }
    }

    return h;

}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
