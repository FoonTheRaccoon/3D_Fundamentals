#pragma once
#include "Vertex.h"
#include "IndexedTriangleList.h"

struct Triangle
{
	Triangle() = default;
	Triangle(Vertex v0, Vertex v1, Vertex v2, Color color)
		: v0(v0), v1(v1), v2(v2), color(color)
	{}
	static std::vector<Triangle> MakeTriangleList(const std::vector<Vertex>& verts,const std::vector<size_t>& tri_indicies_list)
	{
		std::vector<Triangle> tmp_list;
		tmp_list.reserve(tri_indicies_list.size() / 3);
		for (int i = 0; i < tri_indicies_list.size() / 3; ++i)
		{
			tmp_list.emplace_back(
				verts[tri_indicies_list[i * 3]],
				verts[tri_indicies_list[i * 3 + 1]],
				verts[tri_indicies_list[i * 3 + 2]],
				Colors::MakeRGB(rand() % 255, rand() % 255, rand() % 255)
			);
		}
		return tmp_list;
	}
	Vertex v0;
	Vertex v1;
	Vertex v2;
	Color color;
};