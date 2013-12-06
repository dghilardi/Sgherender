#ifndef IMGPLANE_H
#define IMGPLANE_H

#include "types/StructDef.h"
#include <vector>
#include <string>

#include <opencv2/highgui/highgui.hpp>
using namespace std;
class ImgPlane
{
    vector <Color *> image;
    vector<int> raysNumber;
    int width, height;
public:
    ImgPlane(int w, int h);
    void updatePixel(int x, int y, Color &pxl, int rays);
    void writeImg(const string &fileName);
    int getH(){return height;}
    int getW(){return width;}
};

#endif // IMGPLANE_H
