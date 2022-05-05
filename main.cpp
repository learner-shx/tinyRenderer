#include "tgaimage.h"
#include "container.h"
#include "geometry.h"
#include "graphics.h"
#include <iostream>
// #include "draw.h"
#include "model.h"
#include "shader.h"

#define PI 3.11415926535897
extern int Height;
extern int Length;

extern void triangle(v2f* it, Shader &shader, double** zbuffer, TGAImage &image);
int main(int argc, char** argv)
{
    TGAImage image(Length, Height, TGAImage::RGB);
    Model* model;
    // 传入模型的地址
    if(argc >= 2)
        model = new Model(argv[1]);
    else
        model = new Model(".\\obj\\diablo3_pose.obj");
    // 初始化zbuffer

    double** zbuffer = new double* [Height];
    for(int i = 0; i < Height; i++)
        zbuffer[i] = new double [Length];
    
    for(int i = 0; i < Height; i++)
        for(int j = 0; j < Length; j++)
            zbuffer[i][j] = -100.0;
    // 渲染模型
    Shader shader;
    shader.diffusemap_ = model->getDiffusemap();
    for(int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model -> face(i);
        a2v v;
        v2f it[3];
        for(int j = 0; j < 3; j++)
        {
            v.position = model -> vert(face[j]);
            v.normal = model -> normal(i, j);
            v.uv = model -> uv(i, j);
            // v.texColor = model -> texColor(face[j]);
            // std::cout<<v.normal;
            it[j] = shader.vertex(v);
        }
        triangle(it, shader, zbuffer, image);
        // std::cout<<i;
    }
    std::cout<<"finished";

    image.flip_vertically(); // 反转图片
	image.write_tga_file("output.tga");
}

