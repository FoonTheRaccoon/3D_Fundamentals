#pragma once

#include <vector>
#include "Vec3.h"
#include <assert.h>
#include "TexVertex.h"

struct IndexedTriangleList
{
	IndexedTriangleList(TexVertex verts, std::vector<size_t> indices_in)
		:
		verts(std::move(verts)),
		indices(std::move(indices_in))
	{
		assert(indices.size() % 3 == 0);
		cullFlags.resize(indices.size() / 3, false);
	}
	TexVertex verts;
	std::vector<size_t> indices;
	std::vector<bool> cullFlags;
};
