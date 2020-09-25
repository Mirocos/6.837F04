#include <iostream>
#include "scene_parser.h"
#include "camera.h"
#include "image.h"
#include "ray.h"
#include "group.h"
#include "light.h"
//#include "triangle.h"
//#include "transform.h"
//#include "plane.h"
using namespace std;




int main(int argc, char* argv[]){
    const char *input_file = NULL;
    int width = 100;
    int height = 100;
    const char *output_file = NULL;
    float depth_min = 0;
    float depth_max = 1;
    const char *depth_file = NULL;
    const char *normal_file = NULL;
    bool shade_back = false;
// sample command line:
// raytracer -input scene1_1.txt -size 200 200 -output output1_1.tga -depth 9 10 depth1_1.tga

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert (i < argc);
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc);
            width = atoi(argv[i]);
            i++; assert (i < argc);
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc);
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++; assert (i < argc);
            depth_min = atof(argv[i]);
            i++; assert (i < argc);
            depth_max = atof(argv[i]);
            i++; assert (i < argc);
            depth_file = argv[i];
        } else if(!strcmp(argv[i], "-normals")){
            i++; assert(i < argc);
            normal_file = argv[i];
        } else if(!strcmp(argv[i], "-shade_back")){
            shade_back = true;
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
//
    width = std::max(width, height);
    height = width;
    Image *colorImg = new Image(width, height);
    Image *depthImg = new Image(width, height);
    Image *normalImg = new Image(width, height);
//
    assert(input_file != NULL);
    SceneParser *parser = new SceneParser(input_file);

    if(parser){
        colorImg->SetAllPixels(parser->getBackgroundColor());
        depthImg->SetAllPixels(Vec3f(0.f, 0.f, 0.f));
        Camera *camera = parser->getCamera();
        Group *group = parser->getGroup();
        Vec3f ambientLight = parser->getAmbientLight();

        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                float x = (float) i / (float) width;
                float y = 1.0f -  (float) j / (float) height;


                Vec2f point(x, y);
                Ray _r = camera->generateRay(point);
                Hit _h;
                bool intersected =  group->intersect(_r, _h, camera->getTMin());
//                if(y == 0.25f){
//                    printf("x: %f, y: %f ",x, y);cout << "hit" << endl;
//                }


                if(intersected){
//                    colorImg->SetPixel(i, j, _h.getMaterial()->getDiffuseColor());
                    int lightNum = parser->getNumLights();
                    Vec3f diffuseColor = _h.getMaterial()->getDiffuseColor();
                    Vec3f pixelColor = ambientLight * diffuseColor;
                    auto N  = _h.getNormal();
                    if(_r.getDirection().Dot3(N) > 0){
                        if(shade_back){
                            N.Negate();
                        } else{
                            pixelColor = Vec3f(0.f, 0.f, 0.f);
                        }
                    }



                    for(int l = 0; l < lightNum; l++){

                        Light* light = parser->getLight(l);
                        Vec3f L, lightColor;
                        light->getIllumination(_h.getIntersectionPoint(), L, lightColor);


//
                        float diffuse = std::max(L.Dot3(N), 0.0f);
                        pixelColor += lightColor * diffuseColor * diffuse;
//                        cout << "pixel: " << pixelColor << endl;


                    }


//                    cout << "N.length: " << N.Dot3(N) << endl;

                    float t = _h.getT();
                    if(t > depth_max) t = depth_max;
                    if(t < depth_min) t = depth_min;
                    float depth = (depth_max - t) / (depth_max - depth_min);

                    colorImg->SetPixel(i, j, pixelColor);
                    depthImg->SetPixel(i, j, depth * Vec3f(1.f, 1.f, 1.f));
                    normalImg->SetPixel(i, j, Vec3f(fabsf(N.x()), fabsf(N.y()), fabsf(N.z())));
//                    cout<< "normal: " << N << endl;
                }
            }
        }

    }

    if(output_file){
        colorImg->SaveTGA(output_file);
    }
    if(depth_file){
        depthImg->SaveTGA(depth_file);
    }

    if(normal_file){
        normalImg->SaveTGA(normal_file);
    }
//


    return 0;
}