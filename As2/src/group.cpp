

#include "group.h"

Group::Group(int num){
    this->num = num;
    obj.resize(num);
}



bool Group::intersect(const class Ray & r, class Hit & h, float tmin) {
    bool intersected = false;
    for(int i = 0; i < num ; i++){
//        std::cout<<"Start group intersect..."<<std::endl;
        if(obj[i]->intersect(r, h, tmin)){
            intersected = true;

        }

    }
    return intersected;
}

void Group::addObject(int index, class Object3D * obj) {
    this->obj[index] = obj;
}