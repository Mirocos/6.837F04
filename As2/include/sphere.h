
#ifndef _SPHERE_H_
#define _SPHERE_H_



#include "object3d.h"
#include "vectors.h"


class Sphere: public Object3D{
public:
    virtual bool intersect(const Ray &r, Hit &h, float tmin);

    Sphere(const Vec3f &center,const  float &radius, Material* material);
//    ~Sphere();




//    Material* material;  already got in Object3D;
    Vec3f center;
    float radius;


};


#endif