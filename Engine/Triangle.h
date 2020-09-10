#pragma once
#include "Vertex.h"

struct Triangle
{
	Triangle() = default;
	Triangle(Vertex v0, Vertex v1, Vertex v2, Color color)
		: v0(v0), v1(v1), v2(v2), faceNorm((v1.pos - v0.pos).X(v2.pos - v0.pos)), color(color)
	{}
	static Vec3 GetFaceNorm(Vertex v0, Vertex v1, Vertex v2)
	{
		Vec3 tmp = (v1.pos - v0.pos).X(v2.pos - v0.pos);
		tmp.Normalize();
		return tmp;
	}
	void TransformTriangle(const Mat3& rot, const Vec3& pos)
	{
		v0.pos *= rot;
		v1.pos *= rot;
		v2.pos *= rot;
		v0.pos += pos;
		v1.pos += pos;
		v2.pos += pos;

		v0.worldPos = v0.pos;
		v1.worldPos = v1.pos;
		v2.worldPos = v2.pos;

		v0.norm *= rot;
		v1.norm *= rot;
		v2.norm *= rot;

		triCenter = (v0.pos + v1.pos + v2.pos) / 3;

		faceNorm *= rot;
		faceNorm.Normalize();
	}
public:
	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vec3 faceNorm;
	Vec3 triCenter = {0.0f, 0.0f, 0.0f};
	Color color;
};