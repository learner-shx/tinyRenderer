#include "tgaimage.h"
#include "container.h"
#include "geometry.h"
#include <graphics.h>

#include "shader.h"

#define WHITE = EGERGBA(255, 255, 255, 255);
#define RED   = EGERGBA(255, 0,   0,   255);
#define GREEN = EGERGBA(0,   255, 0,   255);
#define BLUE  = EGERGBA(0  , 0, 255,   255);


int Height = 1080;
int Length = 1920;




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
  
Vec3f bicentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P)
{
	Vec3f uv1 = Vec3f((B-A).x, (C-A).x, (A-P).x).crossProduct(
				Vec3f((B-A).y, (C-A).y, (A-P).y)); 
	
	if(std::abs(uv1.z) >= 1e-6)
		uv1 = uv1 * (1/uv1.z);
	// std::cout << P;	
	return uv1;        // orthogonal
}

double bicentricInterplotion(Vec3f uv1, double a, double b, double c)
{
	double ans = uv1.x * b + uv1.y * c + (1 - uv1.x - uv1.y) * a;
	return ans;
}

Vec2f bicentricInterplotion(Vec3f uv1, Vec2f A, Vec2f B, Vec2f C)
{	
	Vec2f ans;
	for(int i = 0; i < 2; i++)
		ans.raw[i] = uv1.x * B.raw[i] + uv1.y * C.raw[i]+ (1 - uv1.x - uv1.y) * A.raw[i];
	return ans;
}

Vec3f bicentricInterplotion(Vec3f uv1, Vec3f A, Vec3f B, Vec3f C)
{	
	Vec3f ans;
	for(int i = 0; i < 3; i++)
		ans.raw[i] = uv1.x * B.raw[i] + uv1.y * C.raw[i]+ (1 - uv1.x - uv1.y) * A.raw[i];
	return ans;
}

Vec4i bicentricInterplotion(Vec3f uv1, Vec4i A, Vec4i B, Vec4i C)
{	
	Vec4i ans;
	for(int i = 0; i < 4; i++)
		ans.raw[i] = uv1.x * B.raw[i] + uv1.y * C.raw[i]+ (1 - uv1.x - uv1.y) * A.raw[i];
	return ans;
}

void triangle(v2f* it, Shader &shader, double** zbuffer, TGAImage &image)
{
	Vec3f A = it[0].pos;
	Vec3f B = it[1].pos;
	Vec3f C = it[2].pos;
	// std::cout<<"start draw a triangle \n" << A << B << C;

	double bboxminx = std::fmin(A.x, std::fmin(B.x, C.x));
	double bboxminy = std::fmin(A.y, std::fmin(B.y, C.y));
	double bboxmaxx = std::fmax(A.x, std::fmax(B.x, C.x));
	double bboxmaxy = std::fmax(A.y, std::fmax(B.y, C.y));

	for(double x = bboxminx; x <= bboxmaxx; x+=0.0005)
	{
		for(double y = bboxminy; y <= bboxmaxy; y+=0.0011)
		{
			Vec3f P = Vec3f(x, y, 0.0);

			// u*B + v*C + (1 - u - v) * A

			Vec3f uv1 = bicentric(A, B, C, P);
			// std::cout << uv1;
	
			double P_z = bicentricInterplotion(uv1, A.z, B.z, C.z);

			if(uv1.x>=-0.0 && uv1.y>=-0.0 && uv1.x+uv1.y <= 1.0)
			{
				// std::cout<<"yes";
				v2f i;
				i.pos = Vec3f(x, y, P_z);
				i.worldPos = bicentricInterplotion(uv1, it[0].worldPos, it[1].worldPos, it[2].worldPos);
				i.worldNormal = bicentricInterplotion(uv1, it[0].worldNormal, it[1].worldNormal, it[2].worldNormal);
				i.uv = bicentricInterplotion(uv1, it[0].uv, it[1].uv, it[2].uv);
				// std::cout << it[0].uv<< it[1].uv<< it[2].uv << i.uv << std::endl;
				int scr_x, scr_y;
				scr_x = (x + 1) / 2 * Length;
				scr_y = (y + 1) / 2 * Height;
				// std::cout<<scr_x<<" "<<scr_y;
				if(scr_x >= 1920 || scr_y >= 1080||scr_x<0||scr_y<0) continue;
				if(zbuffer[scr_y][scr_x] <= P_z)
				{
					// std::cout<<"still still yes";
					// printf("zxy = %f", zbuffer[y][x]);
					// std::cout<<"try to call fragment sahder\n";
					TGAColor color = shader.fragment(i);
					zbuffer[scr_y][scr_x] = P_z;
					// std::cout<<"shader"<<scr_x<<" "<<scr_y<<std::endl;
					image.set(scr_x, scr_y, color);
				}
			}
		}
	}
	// line(A.x, A.y, B.x, B.y, image, white);
	// line(B.x, B.y, C.x, C.y, image, white);
	// line(C.x, C.y, A.x, A.y, image, white);
}