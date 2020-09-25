#include "camera.h"
#include <cmath>

OrthographicCamera::OrthographicCamera(const Vec3f &center,const Vec3f &direction,const Vec3f &up, float size){
    this->size = size;
    this->center = center;

    this->direction = direction;
//    this->direction.Normalize();

    Vec3f::Cross3(horizontal, direction, up);
    Vec3f::Cross3(const_cast<Vec3f &>(up), direction, horizontal);
//    cout << "direction: " << direction << endl;
//    cout << "up:        " << up << endl;
//    cout << "horizontal:" << horizontal << endl;
//    cout << endl;
    this->up = up;
    this->up.Normalize();
    this->direction.Normalize();
    horizontal.Normalize();
    cout << size << endl;

}



//OrthographicCamera::~OrthographicCamera(){
//    delete center;
//    delete direction;
//    delete up;
//    delete horizontal;
//}


Ray OrthographicCamera::generateRay(class Vec2f point) {

    Vec3f origin = center + (point.x() - 0.5) * size * horizontal + (point.y() - 0.5) * size * up;
    return Ray(origin, direction);

}

float OrthographicCamera::getTMin() const{
    return -INFINITY;
}





PerspectiveCamera::PerspectiveCamera(Vec3f &center, Vec3f &direction, Vec3f &up, float angle) {
    this->center = center;
    direction.Normalize();
    Vec3f::Cross3(horizontal, direction, up);
    Vec3f::Cross3(up, direction, horizontal);
    up.Normalize();
    horizontal.Normalize();
    this->up = up;
    this->angle = angle;
    this->direction = direction;

}


float PerspectiveCamera::getTMin() const {
    return 0.f;
}


Ray PerspectiveCamera::generateRay(Vec2f point) {
//    float radians = angle * M_PI / 180.0f;
    float size = 2.f * std::tanf(angle / 2.0f);
    auto p = direction + (point.x() - 0.5) * size * horizontal + (point.y() - 0.5) * size * up;
    Vec3f ray_direction = p;
    ray_direction.Normalize();
    return Ray(center, ray_direction);
}