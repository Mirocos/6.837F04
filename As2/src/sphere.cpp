#include "sphere.h"
#include <cstdio>
#include <cmath>

using namespace std;


Sphere::Sphere(const Vec3f &center, const float &radius, Material* material){
    this->material = material;
    this->center = center;
    this->radius = radius;
}

//Sphere::~Sphere(){
//    assert(center == nullptr);
//    delete center;
//}



bool Sphere::intersect(const class Ray & r, class Hit & h, float tmin) {
    auto direction = r.getDirection();
//    direction.Normalize();
    auto eye_origin = r.getOrigin() - center;

    float a = direction.Dot3(direction); // always be 1 cuz direction is normalized;
    float b = direction.Dot3(eye_origin) * 2;
    float c = eye_origin.Dot3(eye_origin) - radius * radius;
//    printf("%f \n", c);
//    printf("a: %f, b: %f, c: %f\n", a, b ,c);
    float delta = b * b - 4 * a * c;
    bool intersected = false;
//    cout << "delta: " << delta<< endl;
    if(delta >= 0){
        float d = std::sqrt(delta);
        float t_pos = (-b + d) / (2.0f * a);
        float t_neg = (-b - d) / (2.0f * a);
        float t = INFINITY;
        if(t_neg >= tmin){
            t = t_neg;
        }else if(t_pos >= tmin){
            t = t_pos;
        }
        if(t < h.getT()){
            intersected = true;
            Vec3f normal = r.pointAtParameter(t) - center;
            normal.Normalize();
            h.set(t, material, normal, r);
        }


    }

//    if(intersected) cout << "hit" <<endl;
;
    return intersected;

}