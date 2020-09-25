
#include <transform.h>



bool Transform::intersect(const Ray &r, Hit &h, float tmin) {


    auto dir_obj = r.getDirection();
    auto ori_obj = r.getOrigin();

    inverseMatrix.TransformDirection(dir_obj);
    inverseMatrix.Transform(ori_obj);

//  dont normalize the dir_obj so that tos = tws;

    Ray r_obj(ori_obj, dir_obj);
    Hit _h(h.getT(), h.getMaterial(), h.getNormal());
    bool intersected = false;

    if(obj->intersect(r_obj, _h, tmin)){
        intersected = true;
        auto normal = _h.getNormal();
        inverseTransposeMatrix.TransformDirection(normal);
        normal.Normalize();
        h.set(_h.getT(), _h.getMaterial(), normal, r);
    }

    return intersected;
}

Transform::Transform(Matrix &m, Object3D *o) {
    matrix = m;
//    inverseMatrix = Matrix(m);
//    inverseMatrix.Inverse();
    matrix.Inverse(inverseMatrix);
//    cout << "matrix: " << matrix;
//    cout << "inverseMatrix: " << inverseMatrix;
//    assert(matrix == inverseMatrix);
    inverseTransposeMatrix = Matrix(inverseMatrix);
    inverseTransposeMatrix.Transpose();
    obj = o;
}
