#include "camera.h"

#define MAX_REFL 5
#define FLOATRAND ((rand()%10000)/10000.0)
#define NFAST
Camera::Camera(Coord3D _cop, float _distance, float _angle) : cop(_cop), distance(_distance), angle(_angle){
    float dx = tan(angle)*distance;
    float dy = tan(angle)*distance;
    viewPlane.topLeft = Coord3D(dx,dy,cop.getZ()+distance);
    viewPlane.bottomRight = Coord3D(-dx,-dy,cop.getZ()+distance);


    viewPlane.topLeft = Coord3D(-1,1,cop.getZ()+distance);
    viewPlane.bottomRight = Coord3D(1,-1,cop.getZ()+distance);
}

void Camera::getImage(ImgPlane &imagePlane, int samples, Scene &scene, bool fast){
    int width = imagePlane.getW();
    int height = imagePlane.getH();

    float planeWidth = viewPlane.bottomRight.getX()-viewPlane.topLeft.getX();
    float planeHeight = viewPlane.topLeft.getY()-viewPlane.bottomRight.getY();

    string smpls = NumberToString<int>(samples);

    #pragma omp parallel for schedule(dynamic, 1)
    for(int x=0; x<width; ++x){
        PrintUtils::printPercentage(x,width, &smpls);
        for(int y=0; y<height; ++y){
        if(fast){
            float posX = x*planeWidth/(float)width+viewPlane.topLeft.getX();
            double posY = y*planeHeight/(double)height+viewPlane.bottomRight.getY();
            Line ray;
            ray.point = Coord3D(posX,posY,viewPlane.topLeft.getZ());
            ray.direction = (ray.point-cop).norm();

            Coord3D collisionPt;
            SimpleObject *collide = scene.getCollidingObject(ray, collisionPt);
            if(collide!=0){
                Color col = collide->getColor();
                imagePlane.updatePixel(x,y, col, samples);
            }
        }else{
            Color pixelCol(0,0,0);
            for(int sy=0; sy<2; sy++) for(int sx=0;sx<2;sx++){
                Color pixelBuf(0,0,0);
                for(int i=0; i<samples;++i){
                    double r1 = 2*FLOATRAND, r2=2*FLOATRAND;
                    double dx = r1<1 ? sqrt(r1)-1 : 1-sqrt(2-r1);
                    double dy = r2<1 ? sqrt(r2)-1 : 1-sqrt(2-r2);

                    double xf = x+(dx/2-0.5+sx), yf = y+(dy/2-0.5+sy);
                    float posX = xf*planeWidth/(float)width+viewPlane.topLeft.getX();
                    double posY = yf*planeHeight/(double)height+viewPlane.bottomRight.getY();

                    Line ray;
                    ray.point = Coord3D(posX,posY,viewPlane.topLeft.getZ());
                    ray.direction = (ray.point-cop).norm();

                    pixelCol = pixelCol+radiance(ray,0,scene)*(1./samples);
                }
                pixelCol = pixelCol+pixelBuf*0.25;

            }
            pixelCol.clampVars();
            imagePlane.updatePixel(x,y, pixelCol, samples);
        }
    }}

}

Color Camera::radiance(const Line &ray, int depth, Scene &scene, int emis){
    Coord3D collisionPoint;
    SimpleObject *collide = scene.getCollidingObject(ray, collisionPoint);
    assert(abs(collisionPoint.getX())<1.2 && abs(collisionPoint.getY())<1.2);
    if(collide==0) return Color(0,0,0);
    Color col = collide->getColor();

    Coord3D n=collide->getNormal(collisionPoint),
            nl=Coord3D::dotProduct(n,ray.direction)<0?n:Coord3D::scalarMult(n,-1);
    Color objColor=collide->getColor();

    float maxVal = col.getR()>col.getG() && col.getR()>col.getB() ? col.getR() : col.getG() > col.getB() ? col.getG() : col.getB();
    if(maxVal==0.0 || ++depth>MAX_REFL){
        if(FLOATRAND<maxVal) col = col*(1./maxVal);
        else return collide->getEmission()*emis;
    }
    if(collide->getReflectionType()==SimpleObject::DIFFUSE){
        double r1 = 2*M_PI*FLOATRAND,
               r2=FLOATRAND,
               r2s=sqrt(r2);

        Coord3D w=nl,
                u=((fabs(w.getX())>.1?Coord3D(0,1,0):Coord3D::orthonormal(Coord3D(1,0,0),w))).norm(),
                v=Coord3D::orthonormal(w,u);
        Coord3D d = (Coord3D::scalarMult(u,(cos(r1)*r2s)) + Coord3D::scalarMult(v,sin(r1)*r2s) + Coord3D::scalarMult(w,sqrt(1-r2))).norm();
        return collide->getEmission()*emis + Color::elemMult(objColor,radiance(Line(collisionPoint,d.norm()),depth,scene));
    }else if(collide->getReflectionType()==SimpleObject::SPECULAR){
        //cout << "refl collision: (" << collisionPoint.getX() << ", " << collisionPoint.getY() << ", "<< collisionPoint.getZ() << ")" << endl;
        return collide->getEmission()*emis + Color::elemMult(objColor,radiance(Line(collisionPoint,(ray.direction-Coord3D::scalarMult(Coord3D::scalarMult(n,2),Coord3D::dotProduct(n,ray.direction))).norm()),depth,scene));
    }
}
