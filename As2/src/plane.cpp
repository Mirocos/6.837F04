
#include <plane.h>

Plane::Plane(Vec3f &normal, float d, Material *m) {
    material = m;
    normal.Normalize();
    this->normal = normal;
    this->d = d;

    // plane: n · p = d;
    // d is offset, for example , plane(y = 1) equals n(0,0,1) and d = 1
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin) {



    auto origin = r.getOrigin();
    auto dir = r.getDirection();
    float t = (d - normal.Dot3(origin)) / (normal.Dot3(dir));
    bool intersected = false;
    if(t > tmin && t < h.getT()){
        h.set(t, material, normal, r);
        intersected = true;
    }
    return intersected;
}
