


#ifndef ASSIGNMENT_CAMERA_H
#define ASSIGNMENT_CAMERA_H

#include "vectors.h"
#include "ray.h"

class OrthographicCamera;

class Camera{
public:
    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;


};



class OrthographicCamera: public Camera{
public:
    virtual Ray generateRay(Vec2f point) ;
    virtual float getTMin() const ;


    OrthographicCamera(const Vec3f &center,const Vec3f &direction,const Vec3f &up, float size);
//    ~OrthographicCamera();

    Vec3f center;
    Vec3f up;
    Vec3f horizontal;
    Vec3f direction;
    float size;

};




class PerspectiveCamera: public Camera{
public:
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;



    PerspectiveCamera(Vec3f &center, Vec3f &direction, Vec3f &up, float angle);


    Vec3f center;
    Vec3f direction;
    Vec3f up;
    Vec3f horizontal;
    float angle;
};

#endif