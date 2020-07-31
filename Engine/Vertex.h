#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include <vector>
#include "Surface.h"

struct Vertex
{
	Vertex(Vec3 pos = {0.0f, 0.0f, 0.0f}, Vec2 texCor = { 0.0f, 0.0f }, Vec3 color = { float(rand() % 250 + 2), float(rand() % 250 + 2), float(rand() % 250 + 2) })
		: pos(pos), texCor(texCor), color(color)
	{}
	Vertex(const Vertex& other)
		: pos(other.pos), texCor(other.texCor), color(other.color)
	{}
	Vertex(Vertex&& other)
		: pos(std::move(other.pos)), texCor(std::move(other.texCor)), color(std::move(other.color))
	{}
	Vertex& operator=(const Vertex& rhs)
	{
		pos = rhs.pos;
		texCor = rhs.texCor;
		color = rhs.color;
		return *this;
	}
	Vertex InterpolateTo(const Vertex& dest, float alpha) const
	{
		return{
			pos.InterpolateTo(dest.pos,alpha),
			texCor.InterpolateTo(dest.texCor,alpha),
			color.InterpolateTo(dest.color, alpha)
		};
	}
	Vertex& operator+=(const Vertex& rhs)
	{
		pos += rhs.pos;
		texCor += rhs.texCor;
		color += rhs.color;
		return *this;
	}
	Vertex operator+(const Vertex& rhs) const
	{
		return Vertex(*this) += rhs;
	}
	Vertex& operator-=(const Vertex& rhs)
	{
		pos -= rhs.pos;
		texCor -= rhs.texCor;
		color -= rhs.color;
		return *this;
	}
	Vertex operator-(const Vertex& rhs) const
	{
		return Vertex(*this) -= rhs;
	}
	Vertex& operator*=(float rhs)
	{
		pos *= rhs;
		texCor *= rhs;
		color *= rhs;
		return *this;
	}
	Vertex operator*(float rhs) const
	{
		return Vertex(*this) *= rhs;
	}
	Vertex& operator/=(float rhs)
	{
		pos /= rhs;
		texCor /= rhs;
		color /= rhs;
		return *this;
	}
	Vertex operator/(float rhs) const
	{
		return Vertex(*this) /= rhs;
	}
	Vec3 pos;
	Vec2 texCor;
	Vec3 color;
};