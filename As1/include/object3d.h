

#ifndef ASSIGNMENTS_OBJECT3D_H
#define ASSIGNMENTS_OBJECT3D_H

#include "ray.h"
#include "hit.h"
#include "material.h"



class Object3D{
public:
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
//
//    Object3D(Material* material);
//    ~Object3D();


    Material* material = nullptr;


};

#endif