#ifndef __SHADER__
#define __SHADER__

#pragma once

#include "tgaimage.h"
#include "geometry.h"


class a2v
{
public:
    Vec3f position;
    Vec3f normal;
    // Vec4i texColor; 
    Vec2f uv;
    a2v(Vec3f p, Vec3f n, Vec2f u):position(p), normal(n), uv(u){};
    a2v(){};
};

class v2f
{
public:
    Vec3f pos;
    Vec3f worldPos;
    Vec3f worldNormal;
    Vec2f uv;
    
    v2f(Vec3f p, Vec3f wp, Vec3f wn, Vec2f u):pos(p), worldPos(wp), worldNormal(wn), uv(u){};
    v2f(){};
};

class Shader 
{
    public:
    TGAImage diffusemap_;
    Shader(){};
    v2f vertex(a2v v);
    TGAColor fragment(v2f i);
};

#endif //__vUR_GL_H__