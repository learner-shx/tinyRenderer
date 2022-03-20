#include "tgaimage.h"
#include "container.h"
#include "geometry.h"
#include <graphics.h>

#define WHITE = EGERGBA(255, 255, 255, 255);
#define RED   = EGERGBA(255, 0,   0,   255);
#define GREEN = EGERGBA(0,   255, 0,   255);
#define BLUE  = EGERGBA(0  , 0, 255,   255);

extern float fov; // 60'


extern Vec4f MVP(	Vec3f position,
            		Vec3f translate,Vec3f rotate,   Vec3f scale,
            		Vec3f pos,      Vec3f up,       Vec3f dir,
            		Vec4f rtnf);





void draw(int x, int y, ege::color_t color)
{

	setcolor(color);			//设置前景色
	//绘制内容
	fillellipse(x, y, 1, 1);
}


void swap(int &a, int &b)
{
	int temp = b;
	b = a;
	a = temp;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, ege::color_t color)
{
	bool steep = false;
	if(std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int k = 0;
	int dk = std::abs(dy) * 2;

	int y = y0;

	for(int x = x0; x <= x1; x++)
	{
		if(steep)
			draw(x, y, color);
		else
			draw(x, y, color);
		k += dk;
		if(k > dx)
		{
			y += (dy >0 ? 1 : -1);
			k -= std::abs(dx) * 2;
		}
	}
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if(std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int k = 0;
	int dk = std::abs(dy) * 2;

	int y = y0;

	for(int x = x0; x <= x1; x++)
	{
		if(steep)
			image.set(x, y, color);
		else
			image.set(x, y, color);
		k += dk;
		if(k > dx)
		{
			y += (dy >0 ? 1 : -1);
			k -= std::abs(dx) * 2;
		}
	}
}
void triangle(Vec2i A, Vec2i B, Vec2i C, TGAImage &image, TGAColor color)
{

	int bboxminx = std::min(A.x, std::min(B.x, C.x));
	int bboxminy = std::min(A.y, std::min(B.y, C.y));
	int bboxmaxx = std::max(A.x, std::max(B.x, C.x));
	int bboxmaxy = std::max(A.y, std::max(B.y, C.y));

	for(int x = bboxminx; x <= bboxmaxx; x++)
	{
		for(int y = bboxminy; y <= bboxmaxy; y++)
		{
			Vec2i P = Vec2i(x, y);
			Vec3f uv1 = Vec3f((B-A).x, (C-A).x, (A-P).x).crossProduct(
		           		   Vec3f((B-A).y, (C-A).y, (A-P).y));             // orthogonal

			if(std::abs(uv1.z) >= 1e-6)
				uv1 = uv1 * (1/uv1.z);
			// printf("%f, %f, %f\n", uv1.x, uv1.y, uv1.z);
			if(uv1.x>=0 && uv1.y>=0 && uv1.x+uv1.y <= 1)
				image.set(x, y, color);
		}
	}
	// line(A.x, A.y, B.x, B.y, image, white);
	// line(B.x, B.y, C.x, C.y, image, white);
	// line(C.x, C.y, A.x, A.y, image, white);
}

void triangle(Vec2i A, Vec2i B, Vec2i C, TGAImage &image, ege::color_t color)
{

	int bboxminx = std::min(A.x, std::min(B.x, C.x));
	int bboxminy = std::min(A.y, std::min(B.y, C.y));
	int bboxmaxx = std::max(A.x, std::max(B.x, C.x));
	int bboxmaxy = std::max(A.y, std::max(B.y, C.y));

	for(int x = bboxminx; x <= bboxmaxx; x++)
	{
		for(int y = bboxminy; y <= bboxmaxy; y++)
		{
			Vec2i P = Vec2i(x, y);
			Vec3f uv1 = Vec3f((B-A).x, (C-A).x, (A-P).x).crossProduct(
		           		   Vec3f((B-A).y, (C-A).y, (A-P).y));             // orthogonal

			if(std::abs(uv1.z) >= 1e-6)
				uv1 = uv1 * (1/uv1.z);
			// printf("%f, %f, %f\n", uv1.x, uv1.y, uv1.z);
			if(uv1.x>=0 && uv1.y>=0 && uv1.x+uv1.y <= 1)
				draw(x, y,color);
		}
	}
	// line(A.x, A.y, B.x, B.y, image, white);
	// line(B.x, B.y, C.x, C.y, image, white);
	// line(C.x, C.y, A.x, A.y, image, white);
}

void triangle(Vec3f A, Vec3f B, Vec3f C, double** zbuffer, TGAImage &image, ege::color_t color)
{

	int bboxminx = std::min(A.x, std::min(B.x, C.x));
	int bboxminy = std::min(A.y, std::min(B.y, C.y));
	int bboxmaxx = std::max(A.x, std::max(B.x, C.x));
	int bboxmaxy = std::max(A.y, std::max(B.y, C.y));

	for(int x = bboxminx; x <= bboxmaxx; x++)
	{
		for(int y = bboxminy; y <= bboxmaxy; y++)
		{
			Vec3f P = Vec3f(x, y, 0.0);
			Vec3f uv1 = Vec3f((B-A).x, (C-A).x, (A-P).x).crossProduct(
		           		   Vec3f((B-A).y, (C-A).y, (A-P).y));             // orthogonal

			if(std::abs(uv1.z) >= 1e-6)
				uv1 = uv1 * (1/uv1.z);
	
			double P_z = uv1.x * B.z + uv1.y * C.z + (1 - uv1.x - uv1.y) * A.z;

			if(uv1.x>=0 && uv1.y>=0 && uv1.x+uv1.y <= 1)
				if(zbuffer[y][x] < P_z)
				{
					// printf("zxy = %f", zbuffer[y][x]);
					zbuffer[y][x] = P_z;
					draw(x, y, color);

				}
		}
	}
	// line(A.x, A.y, B.x, B.y, image, white);
	// line(B.x, B.y, C.x, C.y, image, white);
	// line(C.x, C.y, A.x, A.y, image, white);
}

void triangle(Vec3f A, Vec3f B, Vec3f C, double** zbuffer, TGAImage &image, TGAColor color)
{

	int bboxminx = std::min(A.x, std::min(B.x, C.x));
	int bboxminy = std::min(A.y, std::min(B.y, C.y));
	int bboxmaxx = std::max(A.x, std::max(B.x, C.x));
	int bboxmaxy = std::max(A.y, std::max(B.y, C.y));

	for(int x = bboxminx; x <= bboxmaxx; x++)
	{
		for(int y = bboxminy; y <= bboxmaxy; y++)
		{
			Vec3f P = Vec3f(x, y, 0.0);
			Vec3f uv1 = Vec3f((B-A).x, (C-A).x, (A-P).x).crossProduct(
		           		   Vec3f((B-A).y, (C-A).y, (A-P).y));             // orthogonal

			if(std::abs(uv1.z) >= 1e-6)
				uv1 = uv1 * (1/uv1.z);
	
			double P_z = uv1.x * B.z + uv1.y * C.z + (1 - uv1.x - uv1.y) * A.z;

			if(uv1.x>=0 && uv1.y>=0 && uv1.x+uv1.y <= 1)
				if(zbuffer[y][x] < P_z)
				{
					// printf("zxy = %f", zbuffer[y][x]);
					
					zbuffer[y][x] = P_z;
					image.set(x, y, color);
				}
		}
	}
	// line(A.x, A.y, B.x, B.y, image, white);
	// line(B.x, B.y, C.x, C.y, image, white);
	// line(C.x, C.y, A.x, A.y, image, white);
}