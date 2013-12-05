#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#include <cmath>

class Coord3D {
private:
    float x, y, z;
public:
    Coord3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Coord3D():x(0),y(0),z(0){}
    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    Coord3D operator+(const Coord3D &pA)const{return Coord3D(pA.x+this->x, pA.y+this->y, pA.z+this->z);}
    Coord3D operator-(const Coord3D &pA)const{return Coord3D(this->x-pA.x, this->y-pA.y, this->z-pA.z);}
    Coord3D &norm(){return *this = Coord3D::scalarMult(*this, (1/sqrt(x*x+y*y+z*z)));}
    static Coord3D crossProduct(const Coord3D &pA, const Coord3D &pB){return Coord3D(pA.y*pB.z-pA.z*pB.y, pA.z*pB.x-pA.x*pB.z, pA.x*pB.y-pA.y*pB.x);}
    static Coord3D scalarMult(const Coord3D &p,float k){return Coord3D(p.x*k,p.y*k,p.z*k);}
    static Coord3D orthonormal(const Coord3D &a, const Coord3D &b){return Coord3D(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
    static float dotProduct(const Coord3D &pA, const Coord3D &pB){return pA.x*pB.x+pA.y*pB.y+pA.z*pB.z;}
};

struct Line {
    Coord3D direction;
    Coord3D point;
    Line(Coord3D pt=Coord3D(0,0,0), Coord3D dir=Coord3D(0,0,0)){point=pt;direction=dir.norm();}
};

class Color {
    float r, g, b;
    float clamp(float val){return val<0?0:val>1?1:val;}
public:
    Color(float _r, float _g, float _b): r(_r), g(_g), b(_b) {}
    float getR(){return r;}
    float getG(){return g;}
    float getB(){return b;}
    void setColor(float _r, float _g, float _b){r=_r; g=_g; b=_b;}
    void clampVars(){r=clamp(r);g=clamp(g);b=clamp(b);}
    Color operator+(const Color &o)const{return Color(r+o.r,g+o.g,b+o.b);}
    Color operator-(const Color &o)const{return Color(r-o.r,g-o.g,b-o.b);}
    Color operator *(float k)const{return Color(k*r,k*g,k*b);}

    static Color elemMult(const Color &a, const Color &b){return Color(a.r*b.r,a.g*b.g,a.b*b.b);}
};

struct Rect {
    Coord3D topLeft, bottomRight;
};

class SimpleObject{
public:
    enum Reflection{DIFFUSE, SPECULAR};

    SimpleObject(Color em, Color col, Reflection rt):emission(em), color(col), reflectionType(rt){}
    virtual bool lineIntersection(const Line &line, Coord3D &result, float &dist) = 0;
    Color getColor(){return color;}
    virtual Coord3D getNormal(const Coord3D &pt) = 0;
    Color getEmission(){return emission;}
    Reflection getReflectionType(){return reflectionType;}

private:
    Color emission, color;
    Reflection reflectionType;
};

#endif // STRUCTDEF_H
