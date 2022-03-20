#include "tgaimage.h"
#include "container.h"
#include "geometry.h"
#include "graphics.h"
#include <iostream>
// #include "draw.h"
#include "model.h"
#define PI 3.11415926535897
int Height = 1080;
int Length = 1920;
float fov = 120 * PI / 180;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const TGAColor blue  = TGAColor(0  , 0, 255,   255);


extern void line(int x0, int y0, int x1, int y1, TGAImage &image, ege::color_t color);
extern void triangle(Vec2i A, Vec2i B, Vec2i C, TGAImage &image, ege::color_t color);
extern void triangle(Vec3f A, Vec3f B, Vec3f C, double** zbuffer, TGAImage &image, ege::color_t color);


extern void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
extern void triangle(Vec2i A, Vec2i B, Vec2i C, TGAImage &image, TGAColor color);
extern void triangle(Vec3f A, Vec3f B, Vec3f C, double** zbuffer, TGAImage &image, TGAColor color);

extern Vec4f MVP(	Vec3f position,
            		Vec3f translate,Vec3f rotate,   Vec3f scale,
            		Vec3f pos,      Vec3f up,       Vec3f dir,
            		Vec4f rtnf);  

int main(int argc, char** argv) {
	TGAImage image(Length, Height, TGAImage::RGB);
	Model* model = new Model(".\\obj\\african_head.obj ");
	// initgraph(Length, Height); 
	double** zbuffer = new double* [Height];
	for(int i = 0; i < Height; i++)
		zbuffer[i] = new double [Length];
	// line(0, 0, 1900, 1000, image, EGERGBA(255, 255, 255, 0));
	for(int i = 0; i < Height; i++)
		for(int j = 0; j < Length; j++)
			zbuffer[i][j] = -100.0;
	
	// for(int i = 0; i < model->nfaces(); i++) 
	// {
	// 	Vec3f coordinate[3];
	// 	for(int j = 0; j < 3; j++)
	// 	{
	// 		coordinate[j] = Vec3f((model->vert(model->face(i)[j]).x ) * Height / 2 + 1. * Length / 2, 
	// 							  (model->vert(model->face(i)[j]).y + 1.) * Height / 2,
	// 							  (model->vert(model->face(i)[j]).z + 1.));
	// 	}
	// 	Vec3f n = (coordinate[2] - coordinate[0]) ^ (coordinate[1] - coordinate[0]);
	// 	n.normalize();
	// 	double intensity = n * Vec3f(0, 0, -1);
	// 	// printf("%f\n", intensity);
	// 	if(intensity > 0.)
	// 		triangle(coordinate[0], coordinate[1], coordinate[2], zbuffer, image, TGAColor(intensity*255, intensity*255, intensity*255, 255));

	// }
	
	// printf("%f\n", zbuffer[11][50]);
	Vec3f light_dir(0,0,-1); // define light_dir


	for (int i=0; i<model->nfaces(); i++) { 
	std::vector<int> face = model->face(i); 
	Vec3f screen_coords[3]; 
	Vec3f world_coords[3]; 
	for (int j=0; j<3; j++) { 
		Vec3f v = model->vert(face[j]); 
		screen_coords[j] = Vec3f((v.x)*Height / 2. + Length / 2., (v.y+1.)*Height/2., (v.z)); 
		world_coords[j]  = v; 
	} 
	Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]); 
	n.normalize();
	double intensity = n * light_dir; 
	// printf("%f\n", intensity);
	// if (intensity>0) { 
		triangle(screen_coords[0], screen_coords[1], screen_coords[2], zbuffer, image, TGAColor(intensity*255, intensity*255, intensity*255, 255)); 
	// } 
	}
	// image.set(50, 41, red);

    // getch();               // 等待输入
    // closegraph();          // 关闭图形界面
	// Matrix test(3, 3);
	// test = {1, 2 ,3 ,4, 5, 6, 7, 8, 9};
	// std::cout << test;
	
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

