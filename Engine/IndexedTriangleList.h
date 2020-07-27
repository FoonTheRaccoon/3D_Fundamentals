#pragma once

#include <vector>
#include "Vec3.h"
#include <assert.h>
#include "Vertex.h"

struct IndexedTriangleList
{
	IndexedTriangleList(std::vector<Vertex> verts, std::vector<size_t> indices_in)
		:
		verts(std::move(verts)),
		indices(std::move(indices_in))
	{
		assert(indices.size() % 3 == 0);
	}
	std::vector<Vertex> verts;
	std::vector<size_t> indices;
	
};
