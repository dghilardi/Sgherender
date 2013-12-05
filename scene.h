#ifndef SCENE_H
#define SCENE_H

#include "types/StructDef.h"
#include "types/triangle.h"
#include "types/sphere.h"
#include <vector>

using namespace std;
class Scene
{
    vector<SimpleObject*> sceneElements;
public:
    Scene();
    SimpleObject *getCollidingObject(const Line &line, Coord3D &collisionPoint);
};

#endif // SCENE_H
