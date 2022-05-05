#include "tgaimage.h"
#include "geometry.h"
#include "transform.h"
#include "shader.h"

#include <iostream>

Vec3f _LightDir = Vec3f(-0.3, -1, 1).normalize();
Vec3f _LightColor = Vec3f(1., 1., 1.);

v2f Shader::vertex(a2v v)
{
    // std::cout<<"vertex shader\n";
    v2f o;
    // std::cout<<v.position;
    // std::cout<<v.normal;
    Matrix M = MVP();
    // std::cout<<M;

    Vec4f position_4d = Vec4f(v.position, 0.0);
    Vec4f normal_4d = Vec4f(v.normal, 0.0);
    // std::cout<<"0";
    o.pos = Vec3f(MVP()*position_4d);
    // std::cout<<o.pos;
    // std::cout<<"1";
    o.worldPos = Vec3f(Object2World()*position_4d);
    // std::cout<<"2";
    o.worldNormal = Vec3f(Normal2World()*normal_4d);
    // std::cout<<"vertex shader succeed\n";
    o.uv = v.uv;
    // std::cout<<v.texColor.x<<" "<<v.texColor.y<<" "<<v.texColor.z<<std::endl;
    return o;
}

TGAColor Shader::fragment(v2f i)
{
    // std::cout<<"fragment shader\n";
    Vec3f worldNormal = i.worldNormal.normalize();

    Vec3f ambient = Vec3f(0.1, 0.1, 0.1);

    Vec3f diffuse = _LightColor * std::fmax(0., _LightDir.dotProduct(worldNormal));

    Vec3f halfv = (GetViewDir(i.worldPos) + _LightDir).normalize();

    Vec3f specular = _LightColor * pow(std::fmax(0., halfv.dotProduct(worldNormal)), 20);

    Vec2f uv = i.uv;
    uv.x *= diffusemap_.get_width();
    uv.y *= diffusemap_.get_height();
    // std::cout<<uv.x<<" "<<uv.y<<std::endl;
    TGAColor tc = diffusemap_.get(int(uv.x), int(uv.y));
    // Vec4i texColor((tc.val|0x00FF0000)>>16, (tc.val|0x00000FF00)>>8, (tc.val|0x000000FF), (tc.val|0xFF000000)>>24);
    // EGERGBA(255, 255, 255, 255)

    Vec3f C = (ambient + diffuse)*Vec3f(double(tc.r), double(tc.g),double(tc.b)) + specular;
    // std::cout << "render a fragment with color " << C << "\n" ;

    return TGAColor(std::min(int(C.x),255), std::min(255, int(C.y)), std::min(255, int(C.z)), 255);

}

