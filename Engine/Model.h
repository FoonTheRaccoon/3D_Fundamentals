#pragma once
#include "Surface.h"
#include "Triangle.h"

class Model
{
public:
	Model(std::vector<Vertex>& verts, std::vector<size_t>& tri_indicies_list, Surface texture = Surface::DefaultSurface())
		: 
		triangles(Triangle::MakeTriangleList(verts, tri_indicies_list)),
		texture(std::move(texture))
	{}
	Model(std::vector<Triangle>& triangles, Surface texture = Surface::DefaultSurface())
		:
		triangles(std::move(triangles)),
		texture(std::move(texture))
	{}
	std::vector<Triangle> triangles;
	Surface texture;
};