#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
  // TODO;
    
    Hit intersection = {NULL, 0, 0};
    double min_t = std::numeric_limits<double>::max();
    double distance = 0;
    
    if(part < 0)
    {
	for(unsigned int i = 0; i < triangles.size(); i++)
	{
		if(Intersect_Triangle(ray, i, distance))
		{
		    if(distance < min_t)
		    {
			min_t = distance;
			intersection.object = this;
			intersection.dist = distance;
			intersection.part = i;
		    }
		}
	}
    }
    else
    {
	if(Intersect_Triangle(ray, part, distance))
	{
	    intersection.object = this;
	    intersection.dist = distance;
	    intersection.part = part;
	}
    }

    return intersection;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
	 
    ivec3 current = triangles[part];
    vec3 u = vertices[current[1]] - vertices[current[0]];
    vec3 v = vertices[current[2]] - vertices[current[0]];
	
    return cross(u,v).normalized();
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{

   ivec3 p = triangles[tri];

   vec3 A = vertices[p[1]] - vertices[p[0]];
   vec3 B = vertices[p[2]] - vertices[p[0]];
   vec3 C = ray.endpoint - vertices[triangles[tri][0]];

   vec3 direction = ray.direction;
   
   // a = alpha
   // b = beta
   // g = gamma

   double b = dot(cross(direction, B), C) / dot(cross(direction, B), A);
   double g = dot(cross(direction, A), C) / dot(cross(direction, A), B);
   double a = 1 - b - g; 

   if(dot(direction, this->Normal(direction,tri)) == 0)
	return false;

   dist = -dot(cross(A,B), C) / dot(cross(A,B), direction);

   if((a < -weight_tol || b < -weight_tol || g < -weight_tol) || dist < small_t)
   {
	return false;
   }

   return true;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
