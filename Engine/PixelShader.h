#pragma once
#include "Colors.h"
#include "Surface.h"
#include "Vertex.h"
#include <cmath>

class Pixel_Shader
{
public:
	virtual Color Effect (const Triangle& tri, const Vertex& pixel)
	{
		return BasePixel(pixel);
	}
	Color BasePixel(const Vertex& pixel)
	{
		//Set texture limits
		const float tex_width = float(texture->GetWidth());
		const float tex_height = float(texture->GetHeight());
		const float tex_clamp_x = tex_width - 1.0f;
		const float tex_clamp_y = tex_height - 1.0f;
		return texture->GetPixel((int)std::fmod(pixel.texCor.x * tex_width, tex_clamp_x), (int)std::fmod(pixel.texCor.y * tex_height, tex_clamp_y));
	}
	void PointToTexture(Surface* tex_in)
	{
		texture = tex_in;
	}
	void IncrementTime(float dt)
	{
		if (time + dt < std::numeric_limits<float>::max())
		{
			time += dt;
			sintime = sin(time);
		}
		else
		{
			time = 0.0f;
			sintime = sin(time);
		}
	}
	void ResetTime()
	{
		time = 0.0f;
		sintime = 0.0f;
	}
protected:
	Surface* texture = nullptr;
	float time = 0.0f;
	float sintime = 0.0f;
};

class Show_Triangles : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const Vertex& pixel) override
	{
		return tri.color;
	}
};

class Show_Vertices : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const Vertex& pixel) override
	{
		return Color(pixel.color);
	}
};



class Solid_White : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const Vertex& pixel) override
	{
		return Colors::White;
	}
};

class Black_White : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const Vertex& pixel) override
	{
		const Color c = BasePixel(pixel);
		const unsigned int avg = (c.GetR() + c.GetG() + c.GetB()) / 3;

		return Colors::MakeRGB(avg, avg, avg);
	}
};

class Invert_Colors : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const const Vertex& pixel) override
	{
		const Color c = BasePixel(pixel);
		return Colors::MakeRGB(255 - c.GetR(), 255 - c.GetG(), 255 - c.GetB());
	}
};

class Static_Colors : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const Vertex& pixel) override
	{
		return Colors::MakeRGB(rand() % 255, rand() % 255, rand() % 255);
	}
};

class Ghost_Shock : public Pixel_Shader
{
public:
	Color Effect(const Triangle& tri, const Vertex& pixel) override
	{
		const Color c = BasePixel(pixel);
		const int r = int(c.GetR() * sintime);
		const int g = int(c.GetG() * sintime);
		const int b = int(c.GetB() * sintime);
		return Colors::MakeRGB(r, g, b);
	}
};


namespace PixelShader
{
	inline Pixel_Shader		Default;
	inline Show_Triangles	ShowTriangles;
	inline Show_Vertices	ShowVerticies;
	inline Solid_White		SolidWhite;
	inline Black_White		BlackAndWhite;
	inline Invert_Colors	InvertColors;
	inline Static_Colors	StaticColors;
	inline Ghost_Shock		GhostShock;

	inline std::vector<Pixel_Shader*> PtrList =
	{
		&Default,
		&ShowTriangles,
		&ShowVerticies,
		&SolidWhite,
		&BlackAndWhite,
		&InvertColors,
		&StaticColors,
		&GhostShock,
	};
}