#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "StructDef.h"
#include <iostream>
#include <cassert>
using namespace std;
class Triangle : public SimpleObject
{
    Coord3D vertA, vertB, vertC;
    Coord3D norm;
    bool sameClockness(const Coord3D &vertexA, const Coord3D &vertexB, const Coord3D &vertexC);
public:
    Triangle(Coord3D vertexA, Coord3D vertexB, Coord3D vertexC, Color col, Color em, Reflection rt);
    bool lineIntersection(const Line &line, Coord3D &result, float &dist);
    Coord3D getNormal(const Coord3D &pt){return norm;}
};

#endif // TRIANGLE_H
