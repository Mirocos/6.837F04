#include "camera.h"


OrthographicCamera::OrthographicCamera(const Vec3f &center,const Vec3f &direction,const Vec3f &up, int size){
    this->size = size;
    this->center = center;

    this->direction = direction;
//    this->direction.Normalize();

    Vec3f::Cross3(horizontal, direction, up);
    Vec3f::Cross3(const_cast<Vec3f &>(up), direction, horizontal);
    cout << "direction: " << direction << endl;
    cout << "up:        " << up << endl;
    cout << "horizontal:" << horizontal << endl;
    cout << endl;
    this->up = up;
    this->up.Normalize();
    this->direction.Normalize();
    horizontal.Normalize();

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