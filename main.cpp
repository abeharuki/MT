#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <assert.h>
#include <imgui.h>

const char kWindowTitle[] = "学籍番号";

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};
struct Matrix4x4 {
	float m[4][4];
};

struct ellipse {
	Vector3 transform;
	int rdius;
	float M;
};


struct Sphere
{
	Vector3 center;//中心点
	float radius;//半径

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

void DrawCenterSphere(
    Sphere sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,
    uint32_t color) {
	const uint32_t kSubdivision = 20;                 // 分割数
	const float pi = 3.14f;                           // π
	const float kLonEvery = 2.0f * pi / kSubdivision; // 経度分割1つ分の角度(φd)
	const float kLatEvery = pi / kSubdivision;        // 緯度分割1つ分の角度(θd)

	// 緯度の方向に分割-π/2~π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex; // 現在の緯度(θ)
		// 経度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度(φ)
			Vector3 a, b, c;
			a = {
			    std::cos(lat) * std::cos(lon) * sphere.radius + sphere.center.x,
			    std::sin(lat) * sphere.radius + sphere.center.y,
			    std::cos(lat) * std::sin(lon) * sphere.radius + sphere.center.z};

			b = {
			    std::cos(lat + kLatEvery) * std::cos(lon) * sphere.radius + sphere.center.x,
			    std::sin(lat + kLatEvery) * sphere.radius + sphere.center.y,
			    std::cos(lat + kLatEvery) * std::sin(lon) * sphere.radius + sphere.center.z};

			c = {
			    std::cos(lat) * std::cos(lon + kLonEvery) * sphere.radius + sphere.center.x,
			    std::sin(lat) * sphere.radius + sphere.center.y,
			    std::cos(lat) * std::sin(lon + kLonEvery) * sphere.radius + sphere.center.z};

			// 正規化デバイス座標系
			Vector3 ndcVertexA = Transform(a, viewProjectionMatrix);
			Vector3 ndcVertexB = Transform(b, viewProjectionMatrix);
			Vector3 ndcVertexC = Transform(c, viewProjectionMatrix);
			// スクリーン座標系
			Vector3 screenVerticesA = Transform(ndcVertexA, viewportMatrix);
			Vector3 screenVerticesB = Transform(ndcVertexB, viewportMatrix);
			Vector3 screenVerticesC = Transform(ndcVertexC, viewportMatrix);

			// ab
			Novice::DrawLine(
			    int(screenVerticesA.x), int(screenVerticesA.y), int(screenVerticesB.x),
			    int(screenVerticesB.y), color);
			// bc
			Novice::DrawLine(
			    int(screenVerticesA.x), int(screenVerticesA.y), int(screenVerticesC.x),
			    int(screenVerticesC.y), color);

			
		}
	}
}

void DrawSphere(
    ellipse* vertexData, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,
    Vector3* f, float r, ellipse planet, Vector3 center, FillMode mode) {
	const uint32_t kSubdivision = 15;                 // 分割数
	const float pi = 3.14f;                           // π
	const float kLonEvery = 2.0f * pi / kSubdivision; // 経度分割1つ分の角度(φd)
	const float kLatEvery = pi / kSubdivision;        // 緯度分割1つ分の角度(θd)
	

	Vector3 direction[1536];//方向ベクトル
	float m[1536]; // 質量
	for (int i = 0; i < 1535; i++) {
		m[i] = 5.972f * (float)pow(5, 5); // 質量
	}
	float r1[1536];   // 距離
	float G = 6.67430f * (float)pow(10, -11); // 万有引力定数

	
	// 緯度の方向に分割-π/2~π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex; // 現在の緯度(θ)
		// 経度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			  
			uint32_t start = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery; // 現在の経度(φ)
		

			// a 左下
			vertexData[start].transform.x = r * cos(lat) * cos(lon) + center.x;
			vertexData[start].transform.y = r * sin(lat) + center.y;
			vertexData[start].transform.z = r * cos(lat) * sin(lon) + center.z;
			
			// b 左上
			vertexData[start + 1].transform.x = r * cos(lat + kLatEvery) * cos(lon) + center.x;
			vertexData[start + 1].transform.y = r * sin(lat + kLatEvery) + center.y;
			vertexData[start + 1].transform.z = r * cos(lat + kLatEvery) * sin(lon) + center.z;
			
			
			// c 右下
			vertexData[start + 2].transform.x = r * cos(lat) * cos(lon + kLonEvery) + center.x;
			vertexData[start + 2].transform.y = r * sin(lat) + center.y;
			vertexData[start + 2].transform.z = r * cos(lat) * sin(lon + kLonEvery) + center.z;
			
			// d 右上
			vertexData[start + 3].transform.x = r * cos(lat + kLatEvery) * cos(lon + kLonEvery)+ center.x;
			vertexData[start + 3].transform.y = r * sin(lat + kLatEvery) + center.y;
			vertexData[start + 3].transform.z = r * cos(lat + kLatEvery) * sin(lon + kLonEvery)+ center.z;
			
			
			// 正規化デバイス座標系
			vertexData[start].transform = Transform(vertexData[start].transform, viewProjectionMatrix);
			vertexData[start + 1].transform = Transform(vertexData[start + 1].transform, viewProjectionMatrix);
			vertexData[start + 2].transform = Transform(vertexData[start + 2].transform, viewProjectionMatrix);
			vertexData[start + 3].transform = Transform(vertexData[start + 3].transform, viewProjectionMatrix);
			
			// スクリーン座標系
			vertexData[start].transform = Transform(vertexData[start].transform, viewportMatrix);
			vertexData[start +1].transform = Transform(vertexData[start + 1].transform, viewportMatrix);
			vertexData[start +2].transform = Transform(vertexData[start + 2].transform, viewportMatrix);
			vertexData[start +3].transform = Transform(vertexData[start + 3].transform, viewportMatrix);
			
			
			//ベクトルの計算                        万有引力と各点の
			direction[start] = Normalize(Subract(planet.transform, vertexData[start].transform));
			direction[start +1] = Normalize(Subract(planet.transform, vertexData[start+1].transform));
			direction[start + 2] = Normalize(Subract(planet.transform, vertexData[start + 2].transform));
			direction[start + 3] = Normalize(Subract(planet.transform, vertexData[start + 3].transform));
			
			
			// 惑星と人の距離
			r1[start] = Length(Subract(planet.transform, vertexData[start].transform));
			r1[start + 1] = Length(Subract(planet.transform, vertexData[start + 1].transform));
			r1[start + 2] = Length(Subract(planet.transform, vertexData[start + 2].transform));
			r1[start + 3] = Length(Subract(planet.transform, vertexData[start + 3].transform));



			//万有引力の大きさ
			f[start] = Multiply(1 / ((int)r1[start] * r1[start]), (Multiply((G * m[start] * planet.M), direction[start])));
			f[start + 1] = Multiply(1 / ((int)r1[start + 1] * r1[start + 1]), (Multiply((G * m[start+1] * planet.M), direction[start + 1])));
			f[start + 2] = Multiply(1 / ((int)r1[start + 2] * r1[start + 2]),(Multiply((G * m[start+2]*planet.M), direction[start + 2])));
			f[start + 3] = Multiply(1 / ((int)r1[start + 3] * r1[start + 3]),(Multiply((G * m[start+3] * planet.M), direction[start + 3])));
			
			
			
			for (int i = 0; i < 1536; i++) {
				vertexData[i].transform = Add(vertexData[i].transform, f[i]);
			}
			/*
			Novice::DrawBox(
			    int(vertexData[0].transform.x/2 ), int(vertexData[0].transform.y/2 ), 5, 5,
			    0.0f,
			    WHITE,
			    kFillModeSolid);
			*/

			Novice::DrawTriangle(
			        int(vertexData[start].transform.x), int(vertexData[start].transform.y),
			        int(vertexData[start + 1].transform.x), int(vertexData[start + 1].transform.y),
			        int(vertexData[start + 2].transform.x), int(vertexData[start + 2].transform.y),
			    BLUE,mode);
			
				

			Novice::DrawTriangle(
			    int(vertexData[start + 1].transform.x), int(vertexData[start + 1].transform.y),
			    int(vertexData[start + 2].transform.x), int(vertexData[start + 2].transform.y),
			    int(vertexData[start + 3].transform.x),
			    int(vertexData[start + 3].transform.y), BLUE, mode);

		    
				
		}
	}

}


void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;                                      // Gridの半分の幅
	const uint32_t kSubdivision = 10;                                       // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 1つ分の長さ
	Vector3 startLine[11];
	Vector3 endLine[11];
	Vector3 ndcVertex1[11];
	Vector3 ndcVertex2[11];
	Vector3 screenVertices1[11];
	Vector3 screenVertices2[11];
	int color;
	// 奥から手前の線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		startLine[xIndex] = {(xIndex * kGridEvery) - kGridHalfWidth, 0, -kGridHalfWidth};
		endLine[xIndex] = {
		    (xIndex * kGridEvery) - kGridHalfWidth, 0,
		    (kGridEvery * kSubdivision) - kGridHalfWidth};
		// 正規化デバイス座標系
		ndcVertex1[xIndex] = Transform(startLine[xIndex], viewProjectionMatrix);
		ndcVertex2[xIndex] = Transform(endLine[xIndex], viewProjectionMatrix);
		// スクリーン座標系
		screenVertices1[xIndex] = Transform(ndcVertex1[xIndex], viewportMatrix);
		screenVertices2[xIndex] = Transform(ndcVertex2[xIndex], viewportMatrix);
		if (xIndex == 5) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}
		Novice::DrawLine(
		    int(screenVertices1[xIndex].x), int(screenVertices1[xIndex].y),
		    int(screenVertices2[xIndex].x), int(screenVertices2[xIndex].y), color);
	}

	// 左から右
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		startLine[zIndex] = {-kGridHalfWidth, 0, (zIndex * kGridEvery) - kGridHalfWidth};
		endLine[zIndex] = {
		    (kGridEvery * kSubdivision) - kGridHalfWidth, 0,
		    (zIndex * kGridEvery) - kGridHalfWidth};
		// 正規化デバイス座標系
		ndcVertex1[zIndex] = Transform(startLine[zIndex], viewProjectionMatrix);
		ndcVertex2[zIndex] = Transform(endLine[zIndex], viewProjectionMatrix);
		// スクリーン座標系
		screenVertices1[zIndex] = Transform(ndcVertex1[zIndex], viewportMatrix);
		screenVertices2[zIndex] = Transform(ndcVertex2[zIndex], viewportMatrix);

		if (zIndex == 5) {
			color = BLACK;
		} else {
			color = 0xAAAAAAFF;
		}
		Novice::DrawLine(
		    int(screenVertices1[zIndex].x), int(screenVertices1[zIndex].y),
		    int(screenVertices2[zIndex].x), int(screenVertices2[zIndex].y), color);
	}
}
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

static const int kWindowWidtht = 1280;
static const int kWindowHeight = 720;

//法線と垂直なベクトルを求める
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidtht, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	FillMode mode = kFillModeSolid;

	Vector3 rotate{ 0,0,0 };
	Vector3 translate{ 0,0,0 };
	
	Vector3 cameraTranslate{0.0f, 1.9f, -5.49f};
	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};





	ellipse planet1[1536];
	

	ellipse planet2[1536];
	
	
	

	//定数
	ellipse planet[3];
	planet[0].transform = {640, 0, 0};
	planet[1].transform = {640, 480, 0};

	Sphere Center[2];
	Center[0].center = {0, 0, 0};
	Center[0].radius = 0.1f;
	Center[1].center = {0, 0, 0};

	Vector3 center = {0.0f, 1.7f, 0};
	Vector3 f[1536] = {0.0f, 0.0f, 0.0f};// 万有引力
	
	
	float r1 = 0.5f;
	float r2 = 0.2f;
	

	Vector2 LR = {10, 1};
	int MousX = 0;
	int MousY= 0;
	
	const float move = 0.02f;
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
		//Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);


		planet[0].M = 5.972f * (float)pow(LR.x, LR.y);
		planet[1].M = 5.972f * (float)pow(LR.x, LR.y);
		Novice::GetMousePosition(&MousX, &MousY);
		
		 
		
		
		//各行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projecttionMatrix = MakePerspectiverFovMatrix(0.45f, float(kWindowWidtht) / float(kWindowHeight), 0.1f, 100.0f);
		//VPMatrixを作る。同次クリップ空間
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projecttionMatrix);
		//ViewportMatrixを作る
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidtht), float(kWindowHeight), 0.0f, 1.0f);


		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && mode == kFillModeSolid) {
			mode = kFillModeWireFrame;

		} else if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && mode == kFillModeWireFrame) {
			mode = kFillModeSolid;
		}


		if (LR.y < 12) {
			if (keys[DIK_RIGHTARROW]) {
				LR.y += 1;
			}
		}

		if (LR.y >= 1) {
			if (keys[DIK_LEFTARROW]) {
				LR.y -= 1;
			}
		} else {
			LR.y = 1;
		}

		
		if (LR.x < 12) {
			if (keys[DIK_UPARROW]) {
				LR.x += 1;
			}
		}

		if (LR.x >= 1) {
			if (keys[DIK_DOWNARROW]) {
				LR.x -= 1;
			}
		} else {
			LR.x = 1;
		}

	
		if (keys[DIK_W]) {
			center.y += move;
			planet[0].transform.y -= 5.8f;
		} else if (keys[DIK_S]) {
			center.y -= move;
			planet[0].transform.y += 5.8f;
		} else if (keys[DIK_D]) {
			center.x += move;

			planet[0].transform.x += 5.8f;
		} else if (keys[DIK_A]) {
			center.x -= move;
			planet[0].transform.x -= 5.8f;
		}

		//planet[0].transform.x = (float)MousX;
		//planet[0].transform.y = (float)MousY;
		
		planet[0].transform.z = Center->center.z;
		//planet[1].transform.x = Center->center.x;
		
	

		ImGui::Begin("Window");
		ImGui::DragFloat3("CamerTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CamerRotate", &cameraRotate.x, 0.01f);

		ImGui::SliderFloat("rdius",&r1,0.01f,1.0f);
		ImGui::SliderFloat("rdius2", &r2, 0.01f, 1.0f);

		ImGui::DragFloat3("center", &center.x, 0.01f);
		ImGui::DragFloat3("planet[0].transform", &planet[0].transform.x, 0.01f);
		ImGui::DragFloat3("planet[1].transform", &planet[1].transform.x, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(100, 150, "%f,%f", LR.x, LR.y);
	
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		//DrawCenterSphere(Center[0], viewProjectionMatrix, viewportMatrix, RED);

		DrawSphere(planet1, viewProjectionMatrix, viewportMatrix, f, r1, planet[0], {0, 0, 0},mode);

		
		DrawSphere(planet2, viewProjectionMatrix, viewportMatrix, f, r2, planet[1], center,mode);
		/*
		Novice::DrawBox(
		    (int)planet[0].transform.x, (int)planet[0].transform.y, 5, 5, 0.0f, WHITE,
		    kFillModeSolid);
		
		
		
		Novice::DrawBox(
		    (int)planet[1].transform.x, (int)planet[1].transform.y, 5, 5, 0.0f, WHITE,
		    kFillModeSolid);
		
		// 惑星
		Novice::DrawEllipse(
		    (int)planet[0].transform.x, (int)planet[0].transform.y, planet[0].rdius,
		    planet[0].rdius, 0.0f, WHITE, kFillModeWireFrame);
		*/
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
