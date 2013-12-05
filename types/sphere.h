#ifndef SPHERE_H
#define SPHERE_H
#include "StructDef.h"
class Sphere : public SimpleObject
{
    Coord3D center;
    double radius;
public:
    Sphere(Coord3D cntr, double rad, Color col, Color em, Reflection rt);
    bool lineIntersection(const Line &line, Coord3D &result, float &dist);
    Coord3D getNormal(const Coord3D &pt);
};

#endif // SPHERE_H
