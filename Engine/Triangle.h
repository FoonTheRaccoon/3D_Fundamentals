#pragma once
#include "Vertex.h"
#include "IndexedTriangleList.h"

struct Triangle
{
	Triangle(Vertex v0, Vertex v1, Vertex v2)
		: v0(v0), v1(v1), v2(v2)
	{}
	static std::vector<Triangle> MakeTriangleList(IndexedTriangleList& list)
	{
		std::vector<Triangle> tmp_list;
		tmp_list.reserve(list.indices.size() / 3);
		for (int i = 0; i < list.indices.size() / 3; ++i)
		{
			tmp_list.emplace_back(
				list.verts[list.indices[i * 3]],
				list.verts[list.indices[i * 3 + 1]],
				list.verts[list.indices[i * 3 + 2]]
			);
		}
		return tmp_list;
	}
	Vertex v0;
	Vertex v1;
	Vertex v2;
	bool cullFlag = false;
};