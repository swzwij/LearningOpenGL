#ifndef NUMERICS_H
#define NUMERICS_H

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

	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(float scalar) : x(scalar), y(scalar) {}
	Vec2(int x, int y) : x((float)x), y((float)y) {}
	Vec2(int scalar) : x((float)scalar), y((float)scalar) {}

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

	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}
	Vec3(int x, int y, int z) : x((float)x), y((float)y), z((float)z) {}
	Vec3(int scalar) : x((float)scalar), y((float)scalar), z((float)scalar) {}

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

	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
	Vec4(int x, int y, int z, int w) : x((float)x), y((float)y), z((float)z), w((float)w) {}
	Vec4(int scalar) : x((float)scalar), y((float)scalar), z((float)scalar), w((float)scalar) {}

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

class Mat3
{
public:
	float m[9];

	Mat3() 
	{
		m[0] = 1; m[1] = 0; m[2] = 0;
		m[3] = 0; m[4] = 1; m[5] = 0;
		m[6] = 0; m[7] = 0; m[8] = 1;
	}

	Mat3(float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22) 
	{
		m[0] = m00; m[1] = m01; m[2] = m02;
		m[3] = m10; m[4] = m11; m[5] = m12;
		m[6] = m20; m[7] = m21; m[8] = m22;
	}

	Mat3(const float* data) 
	{
		for (int i = 0; i < 9; i++)
			m[i] = data[i];
	}

	float& operator[](int index) { return m[index]; }
	const float& operator[](int index) const { return m[index]; }

	Mat3 operator+(const Mat3& other) const 
	{
		Mat3 result;
		for (int i = 0; i < 9; i++)
			result.m[i] = m[i] + other.m[i];
		return result;
	}

	Mat3 operator-(const Mat3& other) const 
	{
		Mat3 result;
		for (int i = 0; i < 9; i++)
			result.m[i] = m[i] - other.m[i];
		return result;
	}

	Mat3 operator*(float scalar) const 
	{
		Mat3 result;
		for (int i = 0; i < 9; i++)
			result.m[i] = m[i] * scalar;
		return result;
	}

	Mat3 operator*(const Mat3& other) const 
	{
		Mat3 result;
		result.m[0] = m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6];
		result.m[1] = m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7];
		result.m[2] = m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8];
		result.m[3] = m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6];
		result.m[4] = m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7];
		result.m[5] = m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8];
		result.m[6] = m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6];
		result.m[7] = m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7];
		result.m[8] = m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8];
		return result;
	}

	Vec3 operator*(const Vec3& vec) const 
	{
		return Vec3
		(
			m[0] * vec.x + m[1] * vec.y + m[2] * vec.z,
			m[3] * vec.x + m[4] * vec.y + m[5] * vec.z,
			m[6] * vec.x + m[7] * vec.y + m[8] * vec.z
		);
	}

	Mat3 Transposed() const 
	{
		return Mat3
		(
			m[0], m[3], m[6],
			m[1], m[4], m[7],
			m[2], m[5], m[8]
		);
	}

	float Determinant() const 
	{
		return m[0] * (m[4] * m[8] - m[5] * m[7]) -
			m[1] * (m[3] * m[8] - m[5] * m[6]) +
			m[2] * (m[3] * m[7] - m[4] * m[6]);
	}

	Mat3 Inverse() const 
	{
		float det = Determinant();
		if (det == 0) 
			return *this;

		float invDet = 1.0f / det;
		Mat3 result;
		result.m[0] = (m[4] * m[8] - m[5] * m[7]) * invDet;
		result.m[1] = (m[2] * m[7] - m[1] * m[8]) * invDet;
		result.m[2] = (m[1] * m[5] - m[2] * m[4]) * invDet;
		result.m[3] = (m[5] * m[6] - m[3] * m[8]) * invDet;
		result.m[4] = (m[0] * m[8] - m[2] * m[6]) * invDet;
		result.m[5] = (m[2] * m[3] - m[0] * m[5]) * invDet;
		result.m[6] = (m[3] * m[7] - m[4] * m[6]) * invDet;
		result.m[7] = (m[1] * m[6] - m[0] * m[7]) * invDet;
		result.m[8] = (m[0] * m[4] - m[1] * m[3]) * invDet;
		return result;
	}

	static Mat3 Identity() { return Mat3(); }

	static Mat3 Scale(float sx, float sy) 
	{
		return Mat3
		(
			sx, 0, 0,
			0, sy, 0,
			0, 0, 1
		);
	}

	static Mat3 Rotation(float angle) 
	{
		float c = cos(angle);
		float s = sin(angle);
		return Mat3
		(
			c, -s, 0,
			s, c, 0,
			0, 0, 1
		);
	}

	static Mat3 Translation(float tx, float ty) 
	{
		return Mat3
		(
			1, 0, tx,
			0, 1, ty,
			0, 0, 1
		);
	}

	const float* ptr() const { return m; }
};

class Mat4
{
public:
	float m[16];

	Mat4() 
	{
		m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
		m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
		m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}

	Mat4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) 
	{
		m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
		m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
		m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
		m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
	}

	Mat4(const float* data) 
	{
		for (int i = 0; i < 16; i++)
			m[i] = data[i];
	}

	float& operator[](int index) { return m[index]; }
	const float& operator[](int index) const { return m[index]; }

	Mat4 operator+(const Mat4& other) const 
	{
		Mat4 result;
		for (int i = 0; i < 16; i++)
			result.m[i] = m[i] + other.m[i];
		return result;
	}

	Mat4 operator-(const Mat4& other) const 
	{
		Mat4 result;
		for (int i = 0; i < 16; i++) 
			result.m[i] = m[i] - other.m[i];
		return result;
	}

	Mat4 operator*(float scalar) const 
	{
		Mat4 result;
		for (int i = 0; i < 16; i++)
			result.m[i] = m[i] * scalar;
		return result;
	}

	Mat4 operator*(const Mat4& other) const 
	{
		Mat4 result;
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				result.m[i * 4 + j] = 0;
				for (int k = 0; k < 4; k++) 
				{
					result.m[i * 4 + j] += m[i * 4 + k] * other.m[k * 4 + j];
				}
			}
		}
		return result;
	}

	Vec4 operator*(const Vec4& vec) const 
	{
		return Vec4
		(
			m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.w,
			m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.w,
			m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] * vec.w,
			m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w
		);
	}

	Vec3 TransformPoint(const Vec3& point) const 
	{
		Vec4 result = *this * Vec4(point.x, point.y, point.z, 1.0f);
		if (result.w != 0) 
			return Vec3(result.x / result.w, result.y / result.w, result.z / result.w);
		
		return Vec3(result.x, result.y, result.z);
	}

	Vec3 TransformDirection(const Vec3& direction) const 
	{
		Vec4 result = *this * Vec4(direction.x, direction.y, direction.z, 0.0f);
		return Vec3(result.x, result.y, result.z);
	}

	Mat4 Transposed() const 
	{
		return Mat4
		(
			m[0], m[4], m[8], m[12],
			m[1], m[5], m[9], m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15]
		);
	}

	float Determinant() const 
	{
		return m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13])) -
			m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12])) +
			m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9] * m[12])) -
			m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9] * m[12]));
	}

	static Mat4 Identity() { return Mat4(); }

	static Mat4 Translation(float tx, float ty, float tz) 
	{
		return Mat4
		(
			1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1
		);
	}

	static Mat4 Scale(float sx, float sy, float sz) 
	{
		return Mat4
		(
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
		);
	}

	static Mat4 RotationX(float angle) 
	{
		float c = cos(angle);
		float s = sin(angle);
		return Mat4
		(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	static Mat4 RotationY(float angle) 
	{
		float c = cos(angle);
		float s = sin(angle);
		return Mat4
		(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	static Mat4 RotationZ(float angle) 
	{
		float c = cos(angle);
		float s = sin(angle);
		return Mat4
		(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	static Mat4 Perspective(float fovy, float aspect, float near, float far) 
	{
		float f = 1.0f / tan(fovy * 0.5f);
		return Mat4
		(
			f / aspect, 0, 0, 0,
			0, f, 0, 0,
			0, 0, (far + near) / (near - far), (2 * far * near) / (near - far),
			0, 0, -1, 0
		);
	}

	static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far) 
	{
		return Mat4
		(
			2 / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, -2 / (far - near), -(far + near) / (far - near),
			0, 0, 0, 1
		);
	}

	static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
	{
		Vec3 f = (center - eye).Normalized();
		Vec3 s = f.Cross(up).Normalized();
		Vec3 u = s.Cross(f);

		Mat4 result;
		result.m[0] = s.x;
		result.m[1] = s.y;
		result.m[2] = s.z;
		result.m[3] = -s.Dot(eye);
		result.m[4] = u.x;
		result.m[5] = u.y;
		result.m[6] = u.z;
		result.m[7] = -u.Dot(eye);
		result.m[8] = -f.x;
		result.m[9] = -f.y;
		result.m[10] = -f.z;
		result.m[11] = f.Dot(eye);
		result.m[12] = 0;
		result.m[13] = 0;
		result.m[14] = 0;
		result.m[15] = 1;

		return result;
	}

	const float* ptr() const { return m; }
};

#endif