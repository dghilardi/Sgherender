#include <iostream>

#include "camera.h"
#include "scene.h"

using namespace std;

int main()
{
    Scene scene;
    Camera cam(Coord3D(0,0,-5),5,3.14*0.25);
    cv::Mat img(800,800,CV_8UC3,cv::Scalar(0));
    cam.getImage(img,scene);
    cv::namedWindow("abc");
    cv::imshow("abc",img);
    cv::imwrite("result.png",img);
    cv::waitKey();
    return 0;
}

