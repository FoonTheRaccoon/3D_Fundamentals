#pragma once
#include "Colors.h"
#include <cmath>

class PixelShader
{
public:
	virtual Color Effect (const Triangle& tri, const Color& c)
	{
		return c;
	}
};

class Show_Triangles : public PixelShader
{
public:
	Color Effect(const Triangle& tri, const Color& c) override
	{
		return tri.color;
	}
};


class Solid_White : public PixelShader
{
public:
	Color Effect(const Triangle& tri, const Color& c) override
	{
		return Colors::White;
	}
};

class Black_White : public PixelShader
{
public:
	Color Effect(const Triangle& tri, const Color& c) override
	{
		const unsigned int avg = (c.GetR() + c.GetG() + c.GetB()) / 3;

		return Colors::MakeRGB(avg, avg, avg);
	}
};

class Invert_Colors : public PixelShader
{
public:
	Color Effect(const Triangle& tri, const Color& c) override
	{
		return Colors::MakeRGB(255 - c.GetR(), 255 - c.GetG(), 255 - c.GetB());
	}
};

namespace Effect
{
	inline PixelShader		Default;
	inline Show_Triangles	ShowTriangles;
	inline Solid_White		SolidWhite;
	inline Black_White		BlackAndWhite;
	inline Invert_Colors	InvertColors;
}