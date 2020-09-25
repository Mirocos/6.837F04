#ifndef _TRANSFORM_H
#define _TRANSFORM_H


#include "object3d.h"
#include "matrix.h"

class Transform: public Object3D{
public:
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    Transform(Matrix &m, Object3D *o);



    Matrix matrix;
    Matrix inverseMatrix;
    Matrix inverseTransposeMatrix;
    Object3D *obj = nullptr;
};

#endif