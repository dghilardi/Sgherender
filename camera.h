#ifndef CAMERA_H
#define CAMERA_H

#include "types/StructDef.h"
#include "utils/printutils.h"
#include "scene.h"
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
class Camera
{
    Coord3D cop;
    Rect viewPlane;
    float distance, angle;
public:
    Camera(Coord3D _cop, float _distance, float _angle);
    void getImage(cv::Mat &image, Scene &scene);
private:
    Color radiance(const Line &ray, int depth, Scene &scene, int emis=1);
};

#endif // CAMERA_H
