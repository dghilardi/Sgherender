#include "triangle.h"

Triangle::Triangle(Coord3D vertexA, Coord3D vertexB, Coord3D vertexC, Color col, Color em, Reflection rt): vertA(vertexA), vertB(vertexB), vertC(vertexC), SimpleObject(em,col,rt)
{
    Coord3D vec1 = vertB-vertA;
    Coord3D vec2 = vertC-vertB;
    norm = Coord3D::crossProduct(vec1,vec2).norm();
}

bool Triangle::lineIntersection(const Line &line, Coord3D &result, float &dist){

    float dotProd = Coord3D::dotProduct(norm,line.direction);
    if(dotProd<0){ //equal to 0 => parallel, >0 => enter from back
        //Compute intersection
        dist = -(Coord3D::dotProduct(norm,line.point-vertA)/Coord3D::dotProduct(norm,line.direction));
        if(dist<0) return false;
        //compute plane intersection point
        result = line.point+Coord3D::scalarMult(line.direction,dist);
        if(sameClockness(vertA,vertB,result) && sameClockness(vertB,vertC,result) &&sameClockness(vertC,vertA,result)){
            return true;
        }
    }
    return false;
}

bool Triangle::sameClockness(const Coord3D &vertexA, const Coord3D &vertexB, const Coord3D &vertexC){
    Coord3D vec1 = vertexB-vertexA;
    Coord3D vec2 = vertexC-vertexB;
    Coord3D compNorm = Coord3D::crossProduct(vec1,vec2);
    float dotProd = Coord3D::dotProduct(compNorm,norm);
    return (dotProd>=0);
}
