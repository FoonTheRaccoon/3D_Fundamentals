#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include <vector>
#include "Surface.h"

struct TexVertex
{
	TexVertex(Vec3 pos = {0.0f, 0.0f, 0.0f}, Vec2 texCor = { 0.0f, 0.0f })
		: pos(pos), texCor(texCor)
	{}
	Vec3 pos;
	Vec2 texCor;
};