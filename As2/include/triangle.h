#ifndef _TRIANGLE_H
#define _TRIANGLE_H


#include "object3d.h"

class Triangle : public  Object3D{
public:
    Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m);

    virtual bool intersect(const Ray &r, Hit &h, float tmin);


    Vec3f A;
    Vec3f B;
    Vec3f C;
    Vec3f normal;

};

#endif