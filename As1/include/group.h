
#ifndef _GROUP_H_
#define _GROUP_H_

#include "object3d.h"
#include <vector>


using namespace std;

//class Object3D;

class Group: public Object3D{
public:
    virtual bool intersect(const Ray &r, Hit &h, float tmin);


    Group(int num);
//    ~Group();
    void addObject(int index, Object3D *obj);

    vector<Object3D*> obj;
    int num = 0;


};

#endif