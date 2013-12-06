#include "imgplane.h"

ImgPlane::ImgPlane(int w, int h) : width(w), height(h)
{
    int size = w*h;
    for(int i=0; i<size; ++i){
        image.push_back(new Color(0,0,0));
        raysNumber.push_back(0);
    }
}

void ImgPlane::updatePixel(int x, int y, Color &pxl, int rays){
    Color *actual = image[x*width+y];
    int actualRays = raysNumber[x*width+y];
    actual->setColor((actual->getR()*actualRays+pxl.getR()*rays)/(rays+actualRays),
                     (actual->getG()*actualRays+pxl.getG()*rays)/(rays+actualRays),
                     (actual->getB()*actualRays+pxl.getB()*rays)/(rays+actualRays)
                     );
    raysNumber[x*width+y] += rays;
}

void ImgPlane::writeImg(const string &fileName){
    cv::Mat img(height, width, CV_8UC3);
    for(int x=0; x<width; ++x) for(int y=0; y<height; ++y){
        Color toAssign = *(image[x*width+y]);
        toAssign.clampVars();
        img.at<uchar>(y,3*x+2) = (uchar)255*toAssign.getR();
        img.at<uchar>(y,3*x+1) = (uchar)255*toAssign.getG();
        img.at<uchar>(y,3*x) = (uchar)255*toAssign.getB();
    }
    cv::imwrite(fileName, img);
}
