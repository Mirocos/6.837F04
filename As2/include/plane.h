#ifndef _PLANE_H
#define _PLANE_H

#include "object3d.h"

class Plane: public Object3D{
public:
    Plane(Vec3f &normal, float d, Material *m);

    virtual bool intersect(const Ray &r, Hit &h, float tmin);


    Vec3f normal;
    float d;

};


#endif