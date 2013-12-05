#include "scene.h"

Scene::Scene()
{
    //sceneElements.push_back(new Triangle(Coord3D(0,0,1),Coord3D(3,0,1),Coord3D(1,1,1)));
    //bottom
    sceneElements.push_back(new Triangle(Coord3D(-1,1,0),Coord3D(1,1,0),Coord3D(-1,1,4), Color(0,0,1.0), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(1,1,4),Coord3D(-1,1,4),Coord3D(1,1,0), Color(0,0,1.0), Color(0,0,0), SimpleObject::DIFFUSE));

    //top
    sceneElements.push_back(new Triangle(Coord3D(1,-1,0),Coord3D(-1,-1,0),Coord3D(-1,-1,4), Color(1.0,1.0,1.0), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(-1,-1,4),Coord3D(1,-1,4),Coord3D(1,-1,0), Color(1.0,1.0,1.0), Color(0,0,0), SimpleObject::DIFFUSE));

    //right
    sceneElements.push_back(new Triangle(Coord3D(1,1,0),Coord3D(1,-1,0),Coord3D(1,-1,4), Color(0.8,0,0.8), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(1,-1,4),Coord3D(1,1,4),Coord3D(1,1,0), Color(0.8,0,0), Color(0,0,0), SimpleObject::DIFFUSE));

    //left
    sceneElements.push_back(new Triangle(Coord3D(-1,-1,0),Coord3D(-1,1,0),Coord3D(-1,-1,4), Color(0,0.8,0.8), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(-1,1,4),Coord3D(-1,-1,4),Coord3D(-1,1,0), Color(0.4,0.8,0.4), Color(0,0,0), SimpleObject::DIFFUSE));

    //back
    sceneElements.push_back(new Triangle(Coord3D(1,-1,4),Coord3D(-1,-1,4),Coord3D(1,1,4), Color(0.3,0.9,0.1), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(-1,1,4),Coord3D(1,1,4),Coord3D(-1,-1,4), Color(0.2,0.5,0.9), Color(0,0,0), SimpleObject::DIFFUSE));

    //light
    sceneElements.push_back(new Triangle(Coord3D(0.8,-1,1.5),Coord3D(0.8,-1,2.5),Coord3D(1,-0.8,1.5), Color(0,0,0), Color(8,8,8), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(1,-0.8,1.5),Coord3D(0.8,-1,2.5),Coord3D(1,-0.8,2.5), Color(0,0,0), Color(8,8,8), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(0.8,-1,2.5),Coord3D(0.8,-1,1.5),Coord3D(1,-0.8,1.5), Color(0,0,0), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(0.8,-1,2.5),Coord3D(1,-0.8,1.5),Coord3D(1,-0.8,2.5), Color(0,0,0), Color(0,0,0), SimpleObject::DIFFUSE));
/*
    sceneElements.push_back(new Triangle(Coord3D(1,-1,0.4),Coord3D(1,-0.6,0),Coord3D(0.6,-1,0), Color(0,0,0), Color(12,12,12), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(-1,1,0.4),Coord3D(-1,0.6,0),Coord3D(-0.6,1,0), Color(0,0,0), Color(12,12,12), SimpleObject::DIFFUSE));

    sceneElements.push_back(new Triangle(Coord3D(-0.5,0,0),Coord3D(0.5,0,0),Coord3D(0,-0.5,0.7071), Color(0,1.0,0), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(0.5,0,0),Coord3D(-0.5,0,0),Coord3D(0,0.5,0.7071), Color(0,1.0,1.0), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(0.5,0,0),Coord3D(0,-0.5,0.7071),Coord3D(0,0.5,0.7071), Color(0,1.0,0), Color(0,0,0), SimpleObject::DIFFUSE));
    sceneElements.push_back(new Triangle(Coord3D(-0.5,0,0),Coord3D(0,0.5,0.7071),Coord3D(0,-0.5,0.7071), Color(0,1.0,0), Color(0,0,0), SimpleObject::DIFFUSE));
*/
//    sceneElements.push_back(new Sphere(Coord3D(0.5,0.5,3),0.4,Color(1.0,0,0),Color(0,0,0),SimpleObject::SPECULAR));
//    sceneElements.push_back(new Sphere(Coord3D(0.5,-0.5,3),0.4,Color(0,1.0,0),Color(0,0,0),SimpleObject::DIFFUSE));
    sceneElements.push_back(new Sphere(Coord3D(-0.5,-0.5,3),0.4,Color(1.0,1.0,1.0),Color(0,0,0),SimpleObject::SPECULAR));
    sceneElements.push_back(new Sphere(Coord3D(0.5,0.5,1),0.4,Color(1.0,1.0,1.0),Color(0,0,0),SimpleObject::DIFFUSE));
//    sceneElements.push_back(new Sphere(Coord3D(-0.5,-0.5,1),0.4,Color(0,0,1.0),Color(0,0,0),SimpleObject::DIFFUSE));
}

SimpleObject *Scene::getCollidingObject(const Line &line, Coord3D &collisionPoint){
    SimpleObject *toReturn = 0;
    float leastDist, dist;
    Coord3D collision;
    for(unsigned int i=0; i<sceneElements.size(); ++i){
        if(sceneElements[i]->lineIntersection(line, collision, dist)){
            if(dist<leastDist || toReturn == 0){
                collisionPoint = collision;
                leastDist = dist;
                toReturn = sceneElements[i];
            }
        }
    }
    return toReturn;
}
