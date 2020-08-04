#pragma once
#include "Vertex.h"
#include "IndexedTriangleList.h"

struct Triangle
{
	Triangle() = default;
	Triangle(Vertex v0, Vertex v1, Vertex v2, Vec3 faceNorm, Color color)
		: v0(v0), v1(v1), v2(v2), faceNorm(faceNorm), color(color)
	{}
	static std::vector<Triangle> MakeTriangleList(const std::vector<Vertex>& verts,const std::vector<size_t>& tri_indicies_list)
	{
		std::vector<Triangle> tmp_list;
		tmp_list.reserve(tri_indicies_list.size() / 3);
		for (int i = 0; i < tri_indicies_list.size() / 3; ++i)
		{
			const Vertex v0 = verts[tri_indicies_list[i * 3]];
			const Vertex v1 = verts[tri_indicies_list[i * 3 + 1]];
			const Vertex v2 = verts[tri_indicies_list[i * 3 + 2]];
			tmp_list.emplace_back(
				v0, v1, v2,
				GetFaceNorm(v0, v1, v2),
				Colors::MakeRGB(rand() % 255, rand() % 255, rand() % 255)
			);
		}
		return tmp_list;
	}
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
};