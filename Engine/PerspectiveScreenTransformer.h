#pragma once
#include "Vec3.h"
#include "Graphics.h"
#include "Triangle.h"

class PerspectiveScreenTransformer
{
public:
	void Transform(Vertex& v ) const
	{
		v.pos *= ProjTrans;
		const float wInv = 1.0f / v.pos.w;

		v.texCor *= wInv;
		v.color *= wInv;

		v.pos.x = (v.pos.x * wInv + 1.0f) * xFactor;
		v.pos.y = (-v.pos.y * wInv + 1.0f) * yFactor;
		v.pos.w = wInv;

	}
	void TransformTri(Triangle& tri) const
	{
		Transform(tri.v0);
		Transform(tri.v1);
		Transform(tri.v2);
	}
	Vertex GetTransformed( const Vertex& v ) const
	{
		Vertex tmp = v;
		Transform(tmp);
		return tmp;
	}
private:
	static constexpr float nearPlane = 0.0f;
	static constexpr float farPlane = 1.0f;
	static constexpr float width = float(Graphics::ScreenWidth);
	static constexpr float height = float(Graphics::ScreenHeight);
	static constexpr float xFactor = width / 2.0f;
	static constexpr float yFactor = height / 2.0f;

	//Projection Transform
	Mat4 ProjTrans = Mat4::ProjectionHFOV(100.0f, (width / height), 1.0f, 10.0f);
};