#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <assert.h>
#include <imgui.h>
#include <algorithm>

const char kWindowTitle[] = "学籍番号";

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4 {
	float m[4][4];
};

struct Sphere
{
	Vector3 center;//中心点
	float radius;//半径

};

struct Line {
	Vector3 origin; //始点
	Vector3 deff; //終点への差分ベクトル
};

struct Ray {
	Vector3 origin; //始点
	Vector3 deff; //終点への差分ベクトル
};

struct Segment {
	Vector3 origin; //始点
	Vector3 deff; //終点への差分ベクトル

};

struct Plane
{
	Vector3 normal;//法線
	float distance;//距離

};

struct Triangle {
	Vector3 vertices[3];//頂点
};


struct AABB {
	Vector3 min;//最小点
	Vector3 max;//最大点

};

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 add;
	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return add;
};

//減算
Vector3 Subract(const Vector3& v1, const Vector3& v2) {
	Vector3 subract;
	subract.x = v1.x - v2.x;
	subract.y = v1.y - v2.y;
	subract.z = v1.z - v2.z;
	return subract;
};

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 multiply;
	multiply.x = v.x * scalar;
	multiply.y = v.y * scalar;
	multiply.z = v.z * scalar;
	return  multiply;
};

//透視投影行列
Matrix4x4 MakePerspectiverFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4  MakePerspectiverFovMatrix;
	MakePerspectiverFovMatrix.m[0][0] = 1 / aspectRatio * (1 / std::tan(fovY / 2));
	MakePerspectiverFovMatrix.m[0][1] = 0.0f;
	MakePerspectiverFovMatrix.m[0][2] = 0.0f;
	MakePerspectiverFovMatrix.m[0][3] = 0.0f;

	MakePerspectiverFovMatrix.m[1][0] = 0.0f;
	MakePerspectiverFovMatrix.m[1][1] = 1 / std::tan(fovY / 2);
	MakePerspectiverFovMatrix.m[1][2] = 0.0f;
	MakePerspectiverFovMatrix.m[1][3] = 0.0f;

	MakePerspectiverFovMatrix.m[2][0] = 0.0f;
	MakePerspectiverFovMatrix.m[2][1] = 0.0f;
	MakePerspectiverFovMatrix.m[2][2] = farClip / (farClip - nearClip);
	MakePerspectiverFovMatrix.m[2][3] = 1.0f;

	MakePerspectiverFovMatrix.m[3][0] = 0.0f;
	MakePerspectiverFovMatrix.m[3][1] = 0.0f;
	MakePerspectiverFovMatrix.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	MakePerspectiverFovMatrix.m[3][3] = 0.0f;

	return MakePerspectiverFovMatrix;
}

//ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 MakeViewportMatrix;
	MakeViewportMatrix.m[0][0] = width / 2.0f;
	MakeViewportMatrix.m[0][1] = 0.0f;
	MakeViewportMatrix.m[0][2] = 0.0f;
	MakeViewportMatrix.m[0][3] = 0.0f;

	MakeViewportMatrix.m[1][0] = 0.0f;
	MakeViewportMatrix.m[1][1] = -height / 2.0f;
	MakeViewportMatrix.m[1][2] = 0.0f;
	MakeViewportMatrix.m[1][3] = 0.0f;

	MakeViewportMatrix.m[2][0] = 0.0f;
	MakeViewportMatrix.m[2][1] = 0.0f;
	MakeViewportMatrix.m[2][2] = maxDepth - minDepth;
	MakeViewportMatrix.m[2][3] = 0.0f;
	MakeViewportMatrix.m[3][0] = left + (width / 2.0f);

	MakeViewportMatrix.m[3][1] = top + (height / 2.0f);
	MakeViewportMatrix.m[3][2] = minDepth;
	MakeViewportMatrix.m[3][3] = 1.0f;
	return MakeViewportMatrix;
}


//回転X
Matrix4x4 MakeRotateXMatrix(float theta = 0) {
	Matrix4x4 MakeRotateMatrix;
	MakeRotateMatrix.m[0][0] = 1;
	MakeRotateMatrix.m[0][1] = 0;
	MakeRotateMatrix.m[0][2] = 0;
	MakeRotateMatrix.m[0][3] = 0;
	MakeRotateMatrix.m[1][0] = 0;
	MakeRotateMatrix.m[1][1] = std::cos(theta);
	MakeRotateMatrix.m[1][2] = std::sin(theta);
	MakeRotateMatrix.m[1][3] = 0;
	MakeRotateMatrix.m[2][0] = 0;
	MakeRotateMatrix.m[2][1] = -std::sin(theta);
	MakeRotateMatrix.m[2][2] = std::cos(theta);
	MakeRotateMatrix.m[2][3] = 0;
	MakeRotateMatrix.m[3][0] = 0;
	MakeRotateMatrix.m[3][1] = 0;
	MakeRotateMatrix.m[3][2] = 0;
	MakeRotateMatrix.m[3][3] = 1;
	return MakeRotateMatrix;

}
//Y
Matrix4x4 MakeRotateYMatrix(float theta = 0) {
	Matrix4x4 MakeRotateMatrix;
	MakeRotateMatrix.m[0][0] = std::cos(theta);
	MakeRotateMatrix.m[0][1] = 0;
	MakeRotateMatrix.m[0][2] = -std::sin(theta);
	MakeRotateMatrix.m[0][3] = 0;
	MakeRotateMatrix.m[1][0] = 0;
	MakeRotateMatrix.m[1][1] = 1;
	MakeRotateMatrix.m[1][2] = 0;
	MakeRotateMatrix.m[1][3] = 0;
	MakeRotateMatrix.m[2][0] = std::sin(theta);;
	MakeRotateMatrix.m[2][1] = 0;
	MakeRotateMatrix.m[2][2] = std::cos(theta);
	MakeRotateMatrix.m[2][3] = 0;
	MakeRotateMatrix.m[3][0] = 0;
	MakeRotateMatrix.m[3][1] = 0;
	MakeRotateMatrix.m[3][2] = 0;
	MakeRotateMatrix.m[3][3] = 1;
	return MakeRotateMatrix;

}
//Z
Matrix4x4 MakeRotateZMatrix(float theta = 0) {
	Matrix4x4 MakeRotateMatrix;
	MakeRotateMatrix.m[0][0] = std::cos(theta);
	MakeRotateMatrix.m[0][1] = std::sin(theta);
	MakeRotateMatrix.m[0][2] = 0;
	MakeRotateMatrix.m[0][3] = 0;
	MakeRotateMatrix.m[1][0] = -std::sin(theta);
	MakeRotateMatrix.m[1][1] = std::cos(theta);
	MakeRotateMatrix.m[1][2] = 0;
	MakeRotateMatrix.m[1][3] = 0;
	MakeRotateMatrix.m[2][0] = 0;
	MakeRotateMatrix.m[2][1] = 0;
	MakeRotateMatrix.m[2][2] = 1;
	MakeRotateMatrix.m[2][3] = 0;
	MakeRotateMatrix.m[3][0] = 0;
	MakeRotateMatrix.m[3][1] = 0;
	MakeRotateMatrix.m[3][2] = 0;
	MakeRotateMatrix.m[3][3] = 1;
	return MakeRotateMatrix;

}


//逆行列
Matrix4x4 Inverse(const  Matrix4x4& m) {
	Matrix4x4 Inverse;
	float A = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	assert(A != 0.0f);
	float B = 1.0f / A;
	Inverse.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * B;
	Inverse.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * B;

	Inverse.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * B;
	Inverse.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * B;

	Inverse.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * B;
	Inverse.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) * B;
	Inverse.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * B;
	Inverse.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) * B;

	Inverse.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) * B;
	Inverse.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) * B;
	Inverse.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) * B;
	Inverse.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * B;

	return Inverse;
};

//スカラー倍
Matrix4x4 Multiply(const Matrix4x4& m1, const  Matrix4x4& m2) {
	Matrix4x4 multiply;
	multiply.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	multiply.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	multiply.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	multiply.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	multiply.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	multiply.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	multiply.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	multiply.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	multiply.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	multiply.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	multiply.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	multiply.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	multiply.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	multiply.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	multiply.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	multiply.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return  multiply;
};

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
};

//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	//回転
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));


	Matrix4x4 MakeAffineMatrix;
	MakeAffineMatrix.m[0][0] = scale.x * rotateXYZMatrix.m[0][0];
	MakeAffineMatrix.m[0][1] = scale.x * rotateXYZMatrix.m[0][1];
	MakeAffineMatrix.m[0][2] = scale.x * rotateXYZMatrix.m[0][2];
	MakeAffineMatrix.m[0][3] = 0;
	MakeAffineMatrix.m[1][0] = scale.y * rotateXYZMatrix.m[1][0];
	MakeAffineMatrix.m[1][1] = scale.y * rotateXYZMatrix.m[1][1];
	MakeAffineMatrix.m[1][2] = scale.y * rotateXYZMatrix.m[1][2];
	MakeAffineMatrix.m[1][3] = 0;
	MakeAffineMatrix.m[2][0] = scale.z * rotateXYZMatrix.m[2][0];
	MakeAffineMatrix.m[2][1] = scale.z * rotateXYZMatrix.m[2][1];
	MakeAffineMatrix.m[2][2] = scale.z * rotateXYZMatrix.m[2][2];
	MakeAffineMatrix.m[2][3] = 0;
	MakeAffineMatrix.m[3][0] = translate.x;
	MakeAffineMatrix.m[3][1] = translate.y;
	MakeAffineMatrix.m[3][2] = translate.z;
	MakeAffineMatrix.m[3][3] = 1;
	return MakeAffineMatrix;


}

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 Cross;
	Cross.x = v1.y * v2.z - v1.z * v2.y;
	Cross.y = v1.z * v2.x - v1.x * v2.z;
	Cross.z = v1.x * v2.y - v1.y * v2.x;

	return Cross;
}

//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 normalize;
	float mag = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalize.x = v.x * mag;
	normalize.y = v.y * mag;
	normalize.z = v.z * mag;
	return normalize;
};

//長さ(ノルマ)
float Length(const Vector3& v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return length;
};

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float dot;
	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return dot;
};


bool IsCollision(const AABB& a, const Sphere& s1) {
	bool collision = false;
	Vector3 closesetPoint{std::clamp(s1.center.x,a.min.x,a.max.x),
						  std::clamp(s1.center.y,a.min.y,a.max.y),
						  std::clamp(s1.center.z,a.min.z,a.max.z) };
	float distance = Length(Subract(closesetPoint, s1.center));

	if (distance <= s1.radius) {


		collision = true;
	}


	return collision;
}


void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20;//分割数
	const float pi = 3.14f;//π
	const float kLonEvery = 2.0f * pi / kSubdivision;//経度分割1つ分の角度(φd)
	const float kLatEvery = pi / kSubdivision;//緯度分割1つ分の角度(θd)

	//緯度の方向に分割-π/2~π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;//現在の緯度(θ)
		//経度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度(φ)
			Vector3 a, b, c;
			a = { std::cos(lat) * std::cos(lon) * sphere.radius + sphere.center.x,
				  std::sin(lat) * sphere.radius + sphere.center.y ,
				  std::cos(lat) * std::sin(lon) * sphere.radius + sphere.center.z };

			b = { std::cos(lat + kLatEvery) * std::cos(lon) * sphere.radius + sphere.center.x ,
				  std::sin(lat + kLatEvery) * sphere.radius + sphere.center.y ,
				  std::cos(lat + kLatEvery) * std::sin(lon) * sphere.radius + sphere.center.z };

			c = { std::cos(lat) * std::cos(lon + kLonEvery) * sphere.radius + sphere.center.x,
				  std::sin(lat) * sphere.radius + sphere.center.y ,
				  std::cos(lat) * std::sin(lon + kLonEvery) * sphere.radius + sphere.center.z };

			//正規化デバイス座標系
			Vector3 ndcVertexA = Transform(a, viewProjectionMatrix);
			Vector3 ndcVertexB = Transform(b, viewProjectionMatrix);
			Vector3 ndcVertexC = Transform(c, viewProjectionMatrix);
			//スクリーン座標系
			Vector3 screenVerticesA = Transform(ndcVertexA, viewportMatrix);
			Vector3 screenVerticesB = Transform(ndcVertexB, viewportMatrix);
			Vector3 screenVerticesC = Transform(ndcVertexC, viewportMatrix);

			//ab
			Novice::DrawLine(int(screenVerticesA.x), int(screenVerticesA.y),
				int(screenVerticesB.x), int(screenVerticesB.y),
				color);
			//bc
			Novice::DrawLine(int(screenVerticesA.x), int(screenVerticesA.y),
				int(screenVerticesC.x), int(screenVerticesC.y),
				color);

		}
	}

}


void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//1つ分の長さ
	Vector3 startLine[11];
	Vector3 endLine[11];
	Vector3 ndcVertex1[11];
	Vector3 ndcVertex2[11];
	Vector3 screenVertices1[11];
	Vector3 screenVertices2[11];
	int color;
	//奥から手前の線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		startLine[xIndex] = { (xIndex * kGridEvery) - kGridHalfWidth ,0,-kGridHalfWidth };
		endLine[xIndex] = { (xIndex * kGridEvery) - kGridHalfWidth    ,0,   (kGridEvery * kSubdivision) - kGridHalfWidth };
		//正規化デバイス座標系
		ndcVertex1[xIndex] = Transform(startLine[xIndex], viewProjectionMatrix);
		ndcVertex2[xIndex] = Transform(endLine[xIndex], viewProjectionMatrix);
		//スクリーン座標系
		screenVertices1[xIndex] = Transform(ndcVertex1[xIndex], viewportMatrix);
		screenVertices2[xIndex] = Transform(ndcVertex2[xIndex], viewportMatrix);
		if (xIndex == 5) {
			color = BLACK;
		}
		else {
			color = 0xAAAAAAFF;
		}
		Novice::DrawLine(int(screenVertices1[xIndex].x), int(screenVertices1[xIndex].y),
			int(screenVertices2[xIndex].x), int(screenVertices2[xIndex].y),
			color);
	}

	//左から右
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		startLine[zIndex] = { -kGridHalfWidth,0,(zIndex * kGridEvery) - kGridHalfWidth };
		endLine[zIndex] = { (kGridEvery * kSubdivision) - kGridHalfWidth     ,0,      (zIndex * kGridEvery) - kGridHalfWidth };
		//正規化デバイス座標系
		ndcVertex1[zIndex] = Transform(startLine[zIndex], viewProjectionMatrix);
		ndcVertex2[zIndex] = Transform(endLine[zIndex], viewProjectionMatrix);
		//スクリーン座標系
		screenVertices1[zIndex] = Transform(ndcVertex1[zIndex], viewportMatrix);
		screenVertices2[zIndex] = Transform(ndcVertex2[zIndex], viewportMatrix);

		if (zIndex == 5) {
			color = BLACK;
		}
		else {
			color = 0xAAAAAAFF;
		}
		Novice::DrawLine(int(screenVertices1[zIndex].x), int(screenVertices1[zIndex].y),
			int(screenVertices2[zIndex].x), int(screenVertices2[zIndex].y),
			color);
	}


}


static const int kRowHeight = 20;
static const int kColumnWidth = 60;

static const int kWindowWidtht = 1280;
static const int kWindowHeight = 720;


//AABBの描画
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 vertex[8];

	Vector3 ndcVertex[8];

	Vector3 screenVertices[8];



	vertex[0] = { aabb.min.x ,aabb.min.y ,aabb.min.z };
	vertex[1] = { aabb.min.x ,aabb.min.y ,aabb.max.z };

	vertex[2] = { aabb.max.x ,aabb.min.y ,aabb.min.z };
	vertex[3] = { aabb.max.x ,aabb.min.y ,aabb.max.z };

	vertex[4] = { aabb.min.x,aabb.max.y , aabb.min.z };
	vertex[5] = { aabb.min.x,aabb.max.y , aabb.max.z };

	vertex[6] = { aabb.max.x,aabb.max.y , aabb.min.z };
	vertex[7] = { aabb.max.x,aabb.max.y , aabb.max.z };


	for (uint32_t Index = 0; Index < 8; ++Index) {
		//正規化デバイス座標系
		ndcVertex[Index] = Transform(vertex[Index], viewProjectionMatrix);
		//スクリーン座標系
		screenVertices[Index] = Transform(ndcVertex[Index], viewportMatrix);
	}

	//底辺
	Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
		int(screenVertices[1].x), int(screenVertices[1].y),
		color);
	Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
		int(screenVertices[2].x), int(screenVertices[2].y),
		color);
	Novice::DrawLine(int(screenVertices[1].x), int(screenVertices[1].y),
		int(screenVertices[3].x), int(screenVertices[3].y),
		color);
	Novice::DrawLine(int(screenVertices[2].x), int(screenVertices[2].y),
		int(screenVertices[3].x), int(screenVertices[3].y),
		color);

	//上辺
	Novice::DrawLine(int(screenVertices[4].x), int(screenVertices[4].y),
		int(screenVertices[5].x), int(screenVertices[5].y),
		color);
	Novice::DrawLine(int(screenVertices[4].x), int(screenVertices[4].y),
		int(screenVertices[6].x), int(screenVertices[6].y),
		color);
	Novice::DrawLine(int(screenVertices[5].x), int(screenVertices[5].y),
		int(screenVertices[7].x), int(screenVertices[7].y),
		color);
	Novice::DrawLine(int(screenVertices[6].x), int(screenVertices[6].y),
		int(screenVertices[7].x), int(screenVertices[7].y),
		color);

	//面
	Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y),
		int(screenVertices[4].x), int(screenVertices[4].y),
		color);
	Novice::DrawLine(int(screenVertices[1].x), int(screenVertices[1].y),
		int(screenVertices[5].x), int(screenVertices[5].y),
		color);
	Novice::DrawLine(int(screenVertices[2].x), int(screenVertices[2].y),
		int(screenVertices[6].x), int(screenVertices[6].y),
		color);
	Novice::DrawLine(int(screenVertices[3].x), int(screenVertices[3].y),
		int(screenVertices[7].x), int(screenVertices[7].y),
		color);


}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidtht, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	AABB aabb1{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},

	};

	Sphere sphere = {
		{ 0.0f,0.0f,0.0f },
		0.5f
	};

	int color = WHITE;


	Vector3 rotate{ 0,0,0 };
	Vector3 translate{ 0,0,0 };
	Vector3 cameraTranslate{ 0.0f,1.9f,-5.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	
	int mouseMovePosX = 0;
	int mouseMovePosY = 0;

	
	const float move = 0.01f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		

		
		if (keys[DIK_SPACE]) {
			Novice::GetMousePosition(&mouseMovePosX, &mouseMovePosY);
			
			
			
			if (mouseMovePosX > 1280/2) {
				cameraRotate.y += move;
			}
			else if (mouseMovePosX < 1280/2) {
				cameraRotate.y -= move;
			}
			/*
			if (mouseMovePosY > 720 / 2) {
				cameraRotate.x += move;
			}
			else if (mouseMovePosY < 720 / 2) {
				cameraRotate.x -= move;
			}
			*/
		}
		

		if (keys[DIK_W]) {
			cameraTranslate.y += move;
		}
		else if (keys[DIK_S]) {
			cameraTranslate.y -= move;
		}
		else if (keys[DIK_D]) {
			cameraTranslate.x += move;
		}
		else if (keys[DIK_A]) {
			cameraTranslate.x -= move;
		}

		int value = Novice::GetWheel();

		if (value > 0) {
			cameraTranslate.z += move * 10;
		}
		else if (value < 0) {
			cameraTranslate.z -= move * 10;
		}

		//各行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projecttionMatrix = MakePerspectiverFovMatrix(0.45f, float(kWindowWidtht) / float(kWindowHeight), 0.1f, 100.0f);
		//VPMatrixを作る。同次クリップ空間
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projecttionMatrix);
		//ViewportMatrixを作る
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidtht), float(kWindowHeight), 0.0f, 1.0f);



		if (IsCollision(aabb1,sphere )) {
			color = RED;
		}
		else {
			color = WHITE;
		}


		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);

		ImGui::Begin("Window");
		ImGui::DragFloat3("CamerRotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("aabb1.min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("aabb1.max", &aabb1.max.x, 0.01f);
		

		

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(viewProjectionMatrix, viewportMatrix);


		DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, color);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, WHITE);



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
