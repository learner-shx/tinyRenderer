#include "geometry.h"
#include <cmath>

#define PI 3.1415926535897

Matrix Model(double t[3] = {0}, double r[3] = {0}, double s[3] =  {0})
{
    for(int i = 0; i < 3; i++)
        r[i] *= PI / 180.;
    
    Matrix scale(4, 4);
    Matrix rotate(4, 4);
    Matrix translate(4, 4);

    scale = 
    {   s[0], 0,    0,    0,
        0,    s[1], 0,    0,
        0,    0,    s[2], 0,
        0,    0,    0,    1
    };

    translate= 
    {   1,    0,    0,    t[0],
        0,    1,    0,    t[1],
        0,    0,    1,    t[2],
        0,    0,    0,    1
    };

    Matrix Rx(3, 3);
    Matrix Ry(3, 3);
    Matrix Rz(3, 3);

    Rx={1,0,0,0,cos(r[0]),-sin(r[0]),0,sin(r[0]),cos(r[0])};
    Ry={cos(r[1]),0,sin(r[1]),0,1,0,-sin(r[1]),0,cos(r[1])};
    Rz={cos(r[2]),-sin(r[2]),0,sin(r[2]),cos(r[2]),0,0,0,1};

    rotate = (Rx * Ry * Rz).mat3to4();

    return translate * rotate * scale;

}

Matrix View(Vec3f pos, Vec3f up, Vec3f dir)
{
    up.normalize();
    dir.normalize();

    Vec3f R, U;

    R = up ^ dir;
    U = dir ^ R;

    Matrix v(4, 4);
    v = 
    {   R.x,   R.y,   R.z,   -pos.x,
        U.x,   U.y,   U.z,   -pos.y,
        dir.x, dir.y, dir.z, -pos.z,
        0,     0,     0,      1
    };

    return v;   
}

Matrix Projection(double r, double t, double n, double f)
{   
    Matrix pro(4, 4);
    pro = 
{       n/r,0,  0,  0,
        0,  n/t,0,  0,
        0,  0,  -(f+n)/(f-n), -2*f*n/(f-n),
        0,  0,  -1, 0
    };
    return pro;
}

Vec4f MVP(  Vec3f position,
            Vec3f translate,Vec3f rotate,   Vec3f scale,
            Vec3f pos,      Vec3f up,       Vec3f dir,
            Vec4f rtnf)
{
    Matrix M(4, 4), V(4, 4), P(4, 4);
    double t[3] = {translate.x, translate.y, translate.z};
    double r[3] = {rotate.x, rotate.y, rotate.z};
    double s[3] = {scale.x, scale.y, scale.z};
    M = Model(t, r, s);
    V = View(pos, up, dir);
    P = Projection(rtnf.x, rtnf.y, rtnf.z, rtnf.w);
    Vec4f position_4d(position.x, position.y, position.z, 1);

    return P * V * M * position_4d;
}

