#pragma once
#include "Colors.h"

class PixelShader
{
public:
	virtual Color Effect (const Color& c)
	{
		return c;
	}
	virtual void Cycle() {};
};


class Solid_White : public PixelShader
{
public:
	Color Effect(const Color& c) override
	{
		return Colors::White;
	}
};

class Black_White : public PixelShader
{
public:
	Color Effect(const Color& c) override
	{
		const unsigned int avg = (c.GetR() + c.GetG() + c.GetB()) / 3;

		return Colors::MakeRGB(avg, avg, avg);
	}
};

class Invert_Colors : public PixelShader
{
public:
	Color Effect(const Color& c) override
	{
		return Colors::MakeRGB(255 - c.GetR(), 255 - c.GetG(), 255 - c.GetB());
	}
};

namespace Effect
{
	inline PixelShader Default;
	inline Solid_White SolidWhite;
	inline Black_White BlackAndWhite;
	inline Invert_Colors InvertColors;
}