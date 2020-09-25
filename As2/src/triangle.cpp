
#include "triangle.h"

Triangle::Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m) {
    A = a;
    B = b;
    C = c;
    material = m;
    Vec3f AB = B - A;
    Vec3f AC = C - A;
    Vec3f::Cross3(normal, AB, AC);
    normal.Normalize();
//    normal.Negate();


}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f rd = r.getDirection();
    Vec3f ro = r.getOrigin();

    float a = A.x() - B.x();
    float b = A.x() - C.x();
    float c = rd.x();
    float d = A.y() - B.y();
    float e = A.y() - C.y();
    float f = rd.y();
    float g = A.z() - B.z();
    float _h = A.z() - C.z();
    float i = rd.z();


    float aBeta = A.x() - ro.x();
    float dBeta = A.y() - ro.y();
    float gBeta = A.z() - ro.z();

    float bGamma = aBeta;
    float eGamma = dBeta;
    float hGamma = gBeta;

    float cT = aBeta;
    float fT = dBeta;
    float iT = gBeta;

    float determineA = a * e * i + b * f * g + c * d * _h - a * f * _h - b * d * i - c * e * g;
    float determineBeta = aBeta * e * i + b * f * gBeta + c * dBeta * _h - aBeta * f * _h - b * dBeta * i - c * e * gBeta;
    float determineGamma = a * eGamma * i + bGamma * f * g + c * d * hGamma - a * f * hGamma - bGamma * d * i - c * eGamma * g;
    float determineT = a * e * iT + b * fT * g + cT * d * _h - a * fT * _h - b * d * iT - cT * e * g;

    float beta = determineBeta / determineA;
    float gamma = determineGamma / determineA;
    float t = determineT / determineA;


    bool intersected = false;
    if((beta > 0 && beta < 1) && (gamma > 0 && gamma < 1) && ((beta + gamma) < 1)){
        if(t > tmin && t < h.getT()){
            intersected  = true;
//            cout << "hit" << endl;
            h.set(t, material, normal, r);

        }
    }


    return intersected;
}
