#include <iostream>

#include "imgplane.h"
#include "camera.h"
#include "scene.h"

using namespace std;

int main()
{
    Scene scene;
    Camera cam(Coord3D(0,0,-5),5,3.14*0.25);
    //cv::Mat img(800,800,CV_8UC3,cv::Scalar(0));
    ImgPlane image(800, 800);
    int samples = 2;
    for(int i=0; i<10; ++i){
        samples*=2;
        cam.getImage(image, samples, scene);
        image.writeImg("result.png");
    }
    /*cv::namedWindow("abc");
    cv::imshow("abc",img);
    cv::imwrite("result.png",img);
    cv::waitKey();*/
    return 0;
}

