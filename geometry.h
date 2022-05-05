#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <vector>
#include <graphics.h>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class t> struct Vec3;
template <class t> struct Vec2 {
	union {
		struct {t u, v;};
		struct {t x, y;};
		t raw[2];
	};
	Vec2() : u(0), v(0) {}
	Vec2(t _u, t _v) : u(_u),v(_v) {}
	inline Vec2<t> operator +(const Vec2<t> &V) const { return Vec2<t>(u+V.u, v+V.v); }
	inline Vec2<t> operator -(const Vec2<t> &V) const { return Vec2<t>(u-V.u, v-V.v); }
	inline Vec2<t> operator *(double f)          const { return Vec2<t>(u*f, v*f); }
	inline Vec2<t> operator *(const Vec2<t> &V) const { return Vec2<t>(V.x*x , V.y*y); }
	inline t  	   operator [](const int n)     {return raw[n];}
	inline t       dotRroduct(const Vec2<t> &V) const { return V.x*x + V.y*y; }

	template <class > friend std::ostream& operator<<(std::ostream& s, Vec2<t>& v);
};

template <class t> struct Vec4 {
	union {
		struct { t x, y, z, w;};
		t raw[4];
	};
	Vec4() : x(0), y(0), z(0) {}
	Vec4(t _x, t _y, t _z, t _w) : x(_x),y(_y),z(_z), w(_w) {}
	Vec4(Vec3<t> v, t _w) : x(v.x), y(v.y), z(v.z), w(_w) {}
	inline Vec4<t> operator ^(const Vec4<t> &v) const { return Vec4<t>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x, w*v.w); }
	inline Vec4<t> operator +(const Vec4<t> &v) const { return Vec4<t>(x+v.x, y+v.y, z+v.z, w+v.w); }
	inline Vec4<t> operator -(const Vec4<t> &v) const { return Vec4<t>(x-v.x, y-v.y, z-v.z, w-v.w); }
	inline Vec4<t> operator *(double f)          const { return Vec4<t>(x*f, y*f, z*f, w*f); }
	inline Vec4<t> operator *(const Vec4<t> &v) const { return Vec4<t>(x*v.x, y*v.y, z*v.z, w*v.w); }
	inline t  	   operator [](const int n)    {return raw[n];}
	inline t	   dotProduct(const Vec4<t> &v) const { return x*v.x + y*v.y + z*v.z + w*v.w;}

	double norm () const { return std::sqrt(x*x+y*y+z*z+w*w); }
	Vec4<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec4<t>& v);
};
template <class t> struct Vec3 {
	union {
		struct {t x, y, z;};
		struct { t ivert, iuv, inorm; };
		t raw[3];
	};
	Vec3() : x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x),y(_y),z(_z) {}
	Vec3(Vec4<t> v) : x(v.x), y(v.y), z(v.z) {}
	inline Vec3<t> operator ^(const Vec3<t> &v) const { return Vec3<t>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	inline Vec3<t> operator +(const Vec3<t> &v) const { return Vec3<t>(x+v.x, y+v.y, z+v.z); }
	inline Vec3<t> operator -(const Vec3<t> &v) const { return Vec3<t>(x-v.x, y-v.y, z-v.z); }
	inline Vec3<t> operator *(double f)          const { return Vec3<t>(x*f, y*f, z*f); }
	inline Vec3<t> operator *(const Vec3<t> &v) const { return Vec3<t>(x*v.x , y*v.y ,z*v.z); }
	inline t  	   operator [](const int n)     {return raw[n];}
	inline t	   dotProduct(const Vec3<t> &v) const { return x*v.x + y*v.y + z*v.z;}
	inline Vec3<t> crossProduct(const Vec3<t> v) const {return Vec3<t>(y*v.z - z*v.y, 
																	   v.x*z - x*v.z,
																	   x*v.y - y*v.x);}
	double norm () const { return std::sqrt(x*x+y*y+z*z); }
	Vec3<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec3<t>& v);
};


typedef Vec2<double> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<double> Vec3f;
typedef Vec3<int>   Vec3i;
typedef Vec4<double> Vec4f;
typedef Vec4<int>   Vec4i;

template <class t> std::ostream& operator<<(std::ostream& s, Vec2<t>& v) {
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream& s, Vec3<t>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}

const int DEFAULT_ALLCOT = 4;

class Matrix
{
	std::vector<std::vector<double> > m;
	int cols, rows;

public:
	Matrix(int r = DEFAULT_ALLCOT, int c = DEFAULT_ALLCOT);
	inline int ncols();
	inline int nrows();
	std::vector<double>& operator[](const int n);
	Matrix operator= (std::initializer_list<double > str);
	Matrix operator= (const Matrix& mat);
	Matrix operator* (const Matrix& n);
	Vec3f operator* (const Vec3f& v);
	Vec4f operator* (const Vec4f& v);
	Matrix mat3to4	();


	Matrix transpose();
	Matrix inverse();

	friend std::ostream& operator<<(std::ostream& s, Matrix& m);
};




#endif //__GEOMETRY_H__
