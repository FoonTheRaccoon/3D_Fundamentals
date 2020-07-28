#pragma once
#include "Vec3.h"
#include "Graphics.h"

class PerspectiveScreenTransformer
{
public:
	PerspectiveScreenTransformer()
		:
		xFactor( float( Graphics::ScreenWidth ) / 2.0f ),
		yFactor( float( Graphics::ScreenHeight ) / 2.0f )
	{}
	Vertex& Transform(Vertex& v ) const
	{
		const float zInv = 1.0f / v.pos.z;

		v.texCor *= zInv;

		v.pos.x = (v.pos.x * zInv + 1.0f) * xFactor;
		v.pos.y = (-v.pos.y * zInv + 1.0f) * yFactor;
		v.pos.z = zInv;
		return v;
	}
	Vertex GetTransformed( const Vertex& v ) const
	{
		return Transform(Vertex( v ) );
	}
private:
	float xFactor;
	float yFactor;
};