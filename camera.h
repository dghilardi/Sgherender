#ifndef CAMERA_H
#define CAMERA_H

#include "types/StructDef.h"
#include "utils/printutils.h"
#include "scene.h"
#include "imgplane.h"

#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>

template <typename T>
  string NumberToString ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }

class Camera
{
    Coord3D cop;
    Rect viewPlane;
    float distance, angle;
public:
    Camera(Coord3D _cop, float _distance, float _angle);
    void getImage(ImgPlane &imagePlane, int samples, Scene &scene, bool fast=false);
private:
    Color radiance(const Line &ray, int depth, Scene &scene, int emis=1);
};

#endif // CAMERA_H
