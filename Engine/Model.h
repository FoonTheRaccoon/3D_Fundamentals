#pragma once
#include "Vertex.h"
#include "Surface.h"
#include "Triangle.h"

class Model
{
public:
	Model(std::vector<Vertex> verts, std::vector<size_t> tri_indicies_list, Surface texture)
		: 
		verts(std::move(verts)),
		tri_indicies_list(std::move(tri_indicies_list)),
		triangles(Triangle::MakeTriangleList(this->verts, this-> tri_indicies_list)),
		texture(std::move(texture))
	{}
	std::vector<Vertex> verts;
	std::vector<size_t> tri_indicies_list;
	std::vector<Triangle> triangles;
	Surface texture;
};