#ifndef __CONTAINER_H__
#define __CONTAINER_H__

class Vector2i
{
public:
    int x;
    int y;
    Vector2i():x(0),y(0){};
    Vector2i(int a, int b):x(a), y(b){};
    int dotProduct(Vector2i v){return v.x*x+v.y*y;};
    Vector2i operator+(Vector2i v){return Vector2i(x+v.x, y+v.y);};
    Vector2i operator-(Vector2i v){return Vector2i(x-v.x, y-v.y);};
    Vector2i operator*(int p){return Vector2i(x*p, y*p);}
    int crossProduct(Vector2i v){return x*v.y - y*v.x;};
};

class Vector2f
{
public:
    float x;
    float y;
    Vector2f():x(0),y(0){};
    Vector2f(float a, float b):x(a), y(b){};
    int dotProduct(Vector2f v){return v.x*x+v.y*y;};
    Vector2f operator+(Vector2f v){return Vector2f(x+v.x, y+v.y);};
    Vector2f operator-(Vector2f v){return Vector2f(x-v.x, y-v.y);};
    Vector2f operator*(float p){return Vector2f(x*p, y*p);}
    int crossProduct(Vector2f v){return x*v.y - y*v.x;};
};


class Vector3i
{
public:
    int x;
    int y;
    int z;
    Vector3i():x(0),y(0),z(0){};
    Vector3i(int a, int b, int c):x(a), y(b), z(c){};
    int dotProduct(Vector3i v){return v.x*x+v.y*y+v.z*z;};
    Vector3i operator+(Vector3i v){return Vector3i(x+v.x, y+v.y, z+v.z);};
    Vector3i operator-(Vector3i v){return Vector3i(x-v.x, y-v.y, z-v.z);};
    Vector3i operator*(int p){return Vector3i(x*p, y*p, z*p);}
    Vector3i crossProduct(Vector3i v){return Vector3i(y*v.z - z*v.y, 
                                                      v.x*z - x*v.z,
                                                      x*v.y - y*v.x);};
};


class Vector3f
{
public:
    float x;
    float y;
    float z;
    Vector3f():x(0),y(0),z(0){};
    Vector3f(float a, float b, float c):x(a), y(b), z(c){};
    int dotProduct(Vector3f v){return v.x*x+v.y*y+v.z*z;};
    Vector3f operator+(Vector3f v){return Vector3f(x+v.x, y+v.y, z+v.z);};
    Vector3f operator-(Vector3f v){return Vector3f(x-v.x, y-v.y, z-v.z);};
    Vector3f operator*(float p){return Vector3f(x*p, y*p, z*p);}
    Vector3f crossProduct(Vector3f v){return Vector3f(y*v.z - z*v.y, 
                                                      v.x*z - x*v.z,
                                                      x*v.y - y*v.x);};
};


class Vector4f
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector4f():x(0),y(0),z(0), w(0){};
    Vector4f(float a, float b, float c, float d):x(a), y(b), z(c), w(d){};
    int dotProduct(Vector4f v){return v.x*x+v.y*y+v.z*z+v.w*w;};
    Vector4f operator+(Vector4f v){return Vector4f(x+v.x, y+v.y, z+v.z, w+v.w);};
    Vector4f operator-(Vector4f v){return Vector4f(x-v.x, y-v.y, z-v.z, w-v.w);};
    Vector4f operator*(float p){return Vector4f(x*p, y*p, z*p, w*p);}
    Vector3f crossProduct(Vector3f v){return Vector3f(y*v.z - z*v.y, 
                                                      v.x*z - x*v.z,
                                                      x*v.y - y*v.x);};
};

class Matrix4f
{
public:
    
};
#endif