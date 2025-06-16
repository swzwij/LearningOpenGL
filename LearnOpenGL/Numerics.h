#pragma once

#include <cmath>

class Vec2;
class Vec3;
class Vec4;
class Mat3;
class Mat4;

class Vec2
{
public:
	float x;
	float y;

	Vec2() : x(0), y(0) { }
	Vec2(float x, float y) : x(x), y(y) { }
	Vec2(float scalar) : x(scalar), y(scalar) { }
	Vec2(int x, int y) : x((float)x), y((float)y) { }
	Vec2(int scalar) : x((float)scalar), y((float)scalar) { }

	Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
	Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
	Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
	Vec2 operator/(float scalar) const { return Vec2(x / scalar, y / scalar); }
	Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
	Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }
	Vec2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
	Vec2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
	
	Vec2 operator-() const { return Vec2(-x, -y); }
	
	Vec2 operator*(int scalar) const { return Vec2(x * scalar, y * scalar); }
	Vec2 operator/(int scalar) const { return Vec2(x / scalar, y / scalar); }
	Vec2& operator*=(int scalar) { x *= scalar; y *= scalar; return *this; }
	Vec2& operator/=(int scalar) { x /= scalar; y /= scalar; return *this; }

	float& operator[](int index) { return (&x)[index]; }
	
	float LengthSquared() const { return x * x + y * y; }
	float Length() const { return sqrt(LengthSquared()); }
	Vec2 Normalized() const { float l = Length(); return l > 0 ? *this / l : Vec2(); }
	float Dot(const Vec2& other) const { return x * other.x + y * other.y; }

	const float* ptr() const { return &x; }
};

class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3() : x(0), y(0), z(0) { }
	Vec3(float x, float y, float z) : x(x), y(y), z(z) { }
	Vec3(float scalar) : x(scalar), y(scalar), z(scalar) { }
	Vec3(int x, int y, int z) : x((float)x), y((float)y), z((float)z) { }
	Vec3(int scalar) : x((float)scalar), y((float)scalar), z((float)scalar) { }

	Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
	Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
	Vec3 operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
	Vec3 operator/(float scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }
	Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vec3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
	Vec3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

	Vec3 operator-() const { return Vec3(-x, -y, -z); }

	Vec3 operator*(int scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
	Vec3 operator/(int scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }
	Vec3& operator*=(int scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
	Vec3& operator/=(int scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

	float& operator[](int index) { return (&x)[index]; }

	float LengthSquared() const { return x * x + y * y + z * z; }
	float Length() const { return sqrt(LengthSquared()); }
	Vec3 Normalized() const { float l = Length(); return l > 0 ? *this / l : Vec3(); }
	float Dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
	Vec3 Cross(const Vec3& other) const { return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

	const float* ptr() const { return &x; }
};

class Vec4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vec4() : x(0), y(0), z(0), w(0) { }
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	Vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }
	Vec4(int x, int y, int z, int w) : x((float)x), y((float)y), z((float)z), w((float)w) { }
	Vec4(int scalar) : x((float)scalar), y((float)scalar), z((float)scalar), w((float)scalar) { }

	Vec4 operator+(const Vec4& other) const { return Vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
	Vec4 operator-(const Vec4& other) const { return Vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
	Vec4 operator*(float scalar) const { return Vec4(x * scalar, y * scalar, z * scalar, w * scalar); }
	Vec4 operator/(float scalar) const { return Vec4(x / scalar, y / scalar, z / scalar, w / scalar); }
	Vec4& operator+=(const Vec4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	Vec4& operator-=(const Vec4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	Vec4& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
	Vec4& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

	Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }

	Vec4 operator*(int scalar) const { return Vec4(x * scalar, y * scalar, z * scalar, w * scalar); }
	Vec4 operator/(int scalar) const { return Vec4(x / scalar, y / scalar, z / scalar, w / scalar); }
	Vec4& operator*=(int scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
	Vec4& operator/=(int scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

	float& operator[](int index) { return (&x)[index]; }

	float LengthSquared() const { return x * x + y * y + z * z + w * w; }
	float Length() const { return sqrt(LengthSquared()); }
	Vec4 Normalized() const { float l = Length(); return l > 0 ? *this / l : Vec4(); }
	float Dot(const Vec4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

	Vec3 xyz() const { return Vec3(x, y, z); }
	Vec3 rgb() const { return Vec3(x, y, z); }

	const float* ptr() const { return &x; }
};