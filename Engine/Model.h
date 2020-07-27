#pragma once
#include "Vertex.h"
#include "Surface.h"

class Model
{
public:
	Model(std::vector<Vertex> verts, Surface texture = Surface::DefaultSurface())
		: verts(std::move(verts)), texture(std::move(texture))
	{}
	std::vector<Vertex> verts;
	Surface texture;
};