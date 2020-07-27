#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include <vector>
#include "Surface.h"

struct Vertex
{
	Vertex(Vec3 pos = {0.0f, 0.0f, 0.0f}, Vec2 texCor = { 0.0f, 0.0f })
		: pos(pos), texCor(texCor)
	{}
	Vertex InterpolateTo(const Vertex& dest, float alpha) const
	{
		return{
			pos.InterpolateTo(dest.pos,alpha),
			texCor.InterpolateTo(dest.texCor,alpha)
		};
	}
	Vertex& operator+=(const Vertex& rhs)
	{
		pos += rhs.pos;
		texCor += rhs.texCor;
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
		return *this;
	}
	Vertex operator/(float rhs) const
	{
		return Vertex(*this) /= rhs;
	}
	Vec3 pos;
	Vec2 texCor;
	bool cullFlag = false;
};