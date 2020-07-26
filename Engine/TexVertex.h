#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include <vector>
#include "Surface.h"

struct TexVertex
{
	TexVertex(std::vector<Vec3> pos = std::vector<Vec3>(0), std::vector<Vec2> texCor = std::vector<Vec2>(0))
		: pos(pos), texCor(texCor)
	{}
	std::vector<Vec3> pos;
	std::vector<Vec2> texCor;
};