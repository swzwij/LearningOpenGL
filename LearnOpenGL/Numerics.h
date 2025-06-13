#pragma once

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
};