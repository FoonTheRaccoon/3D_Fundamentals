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
	TexVertex InterpolateTo(const TexVertex& dest, float alpha) const
	{
		return{
			pos.InterpolateTo(dest.pos,alpha),
			texCor.InterpolateTo(dest.texCor,alpha)
		};
	}
	TexVertex& operator+=(const TexVertex& rhs)
	{
		pos += rhs.pos;
		texCor += rhs.texCor;
		return *this;
	}
	TexVertex operator+(const TexVertex& rhs) const
	{
		return TexVertex(*this) += rhs;
	}
	TexVertex& operator-=(const TexVertex& rhs)
	{
		pos -= rhs.pos;
		texCor -= rhs.texCor;
		return *this;
	}
	TexVertex operator-(const TexVertex& rhs) const
	{
		return TexVertex(*this) -= rhs;
	}
	TexVertex& operator*=(float rhs)
	{
		pos *= rhs;
		texCor *= rhs;
		return *this;
	}
	TexVertex operator*(float rhs) const
	{
		return TexVertex(*this) *= rhs;
	}
	TexVertex& operator/=(float rhs)
	{
		pos /= rhs;
		texCor /= rhs;
		return *this;
	}
	TexVertex operator/(float rhs) const
	{
		return TexVertex(*this) /= rhs;
	}
	Vec3 pos;
	Vec2 texCor;
};