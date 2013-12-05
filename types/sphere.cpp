#include "sphere.h"

Sphere::Sphere(Coord3D cntr, double rad, Color col, Color em, Reflection rt): center(cntr), radius(rad), SimpleObject(em,col,rt)
{
}

bool Sphere::lineIntersection(const Line &line, Coord3D &result, float &dist){
    Coord3D op = center-line.point; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    double eps=1e-2,
            b=Coord3D::dotProduct(op,line.direction),
            det=b*b-Coord3D::dotProduct(op,op)+radius*radius;
    if (det<0) return false;
    else det=sqrt(det);

    if(b-det>eps) dist=b-det;
    else if(b+det>eps) dist=b+det;
    else return false;
    result = line.point+Coord3D::scalarMult(line.direction,dist);
    return true;
}

Coord3D Sphere::getNormal(const Coord3D &pt){
    return (pt-center).norm();
}
