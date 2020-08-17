#pragma once
#include "Vertex.h"
#include "IndexedTriangleList.h"

struct Triangle
{
	Triangle() = default;
	Triangle(Vertex v0, Vertex v1, Vertex v2, Vec3 faceNorm, Color color)
		: v0(v0), v1(v1), v2(v2), faceNorm(faceNorm), color(color)
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

		faceNorm = (v1.pos - v0.pos).X(v2.pos - v0.pos);
		faceNorm.Normalize();
	}
public:
	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vec3 faceNorm;
	Color color;
	float lightBias = 1.0f;
};