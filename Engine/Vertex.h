#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include <vector>
#include "Surface.h"

struct Vertex
{
	Vertex(Vec3 pos = {0.0f, 0.0f, 0.0f}, Vec2 texCor = { 0.0f, 0.0f }, Vec3 norm = { 0.0f, 0.0f, 0.0f }, Vec3 color = { float(rand() % 250 + 2), float(rand() % 250 + 2), float(rand() % 250 + 2) }, Vec3 worldPos = { 0.0f, 0.0f, 0.0f })
		: pos(pos), texCor(texCor), norm(norm), color(color), worldPos(worldPos)
	{}
	Vertex(const Vertex& other)
		: pos(other.pos), texCor(other.texCor), norm(other.norm), color(other.color), worldPos(other.worldPos)
	{}
	Vertex(Vertex&& other)
		: pos(std::move(other.pos)), texCor(std::move(other.texCor)), norm(std::move(other.norm)), color(std::move(other.color)), worldPos(std::move(other.worldPos))
	{}
	Vertex& operator=(const Vertex& rhs)
	{
		pos = rhs.pos;
		texCor = rhs.texCor;
		color = rhs.color;
		worldPos = rhs.worldPos;
		return *this;
	}
	Vertex InterpolateTo(const Vertex& dest, float alpha) const
	{
		return{
			pos.InterpolateTo(dest.pos,alpha),
			texCor.InterpolateTo(dest.texCor,alpha),
			norm.InterpolateTo(dest.norm,alpha),
			color.InterpolateTo(dest.color, alpha),
			worldPos.InterpolateTo(dest.worldPos,alpha),
		};
	}
	Vertex& operator+=(const Vertex& rhs)
	{
		pos += rhs.pos;
		texCor += rhs.texCor;
		norm += rhs.norm;
		color += rhs.color;
		worldPos += rhs.worldPos;
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
		norm -= rhs.norm;
		color -= rhs.color;
		worldPos -= rhs.worldPos;
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
		norm *= rhs;
		color *= rhs;
		worldPos *= rhs;
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
		norm /= rhs;
		color /= rhs;
		worldPos /= rhs;
		return *this;
	}
	Vertex operator/(float rhs) const
	{
		return Vertex(*this) /= rhs;
	}
	static Vertex PixelReadyToDraw(const Vertex base, const float z)
	{
		Vertex pixel = base;
		pixel.texCor *= z;
		pixel.color *= z;
		return pixel;
	}
	Vec3 pos;
	Vec2 texCor;
	Vec3 norm;
	Vec3 color;
	Vec3 worldPos;
};