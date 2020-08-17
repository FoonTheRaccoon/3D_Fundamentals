#pragma once
#include "Surface.h"
#include "Triangle.h"

class Model
{
public:
	Model(std::vector<Triangle>& triangles, Surface texture = Surface::DefaultSurface())
		:
		triangles(std::move(triangles)),
		texture(std::move(texture))
	{}
	std::vector<Triangle> triangles;
	Surface texture;
};