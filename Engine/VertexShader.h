#pragma once
#include "Vertex.h"

class Vertex_Shader
{
public:
	virtual Triangle Effect(Triangle& tri)
	{
		return tri;
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
	float time = 0.0f;
	float sintime = 0.0f;
};

class Float_Object : public Vertex_Shader
{
public:
	Triangle Effect(Triangle& tri) override
	{
		tri.v0.pos.y = tri.v0.pos.y + (sintime / 6);
		tri.v1.pos.y = tri.v1.pos.y + (sintime / 6);
		tri.v2.pos.y = tri.v2.pos.y + (sintime / 6);

		return tri;
	}
};

class Pulse_Object : public Vertex_Shader
{
public:
	Triangle Effect(Triangle& tri) override
	{
		tri.v0.pos.y = tri.v0.pos.y + (tri.v0.pos.y * sintime / 6);
		tri.v1.pos.y = tri.v1.pos.y + (tri.v1.pos.y * sintime / 6);
		tri.v2.pos.y = tri.v2.pos.y + (tri.v2.pos.y * sintime / 6);
													 
		tri.v0.pos.x = tri.v0.pos.x + (tri.v0.pos.x * sintime / 6);
		tri.v1.pos.x = tri.v1.pos.x + (tri.v1.pos.x * sintime / 6);
		tri.v2.pos.x = tri.v2.pos.x + (tri.v2.pos.x * sintime / 6);

		return tri;
	} 
};

class X_Wobble : public Vertex_Shader
{
public:
	Triangle Effect(Triangle& tri) override
	{
		tri.v0.pos.x = tri.v0.pos.x + (tri.v0.pos.x * sin(time * tri.v0.pos.y * 10.0f) / 6);
		tri.v1.pos.x = tri.v1.pos.x + (tri.v1.pos.x * sin(time * tri.v1.pos.y * 10.0f) / 6);
		tri.v2.pos.x = tri.v2.pos.x + (tri.v2.pos.x * sin(time * tri.v2.pos.y * 10.0f) / 6);

		return tri;
	}
};


namespace VertexShader
{
	inline Vertex_Shader	Default;
	inline Float_Object		FloatObject;
	inline Pulse_Object		PulseObject;
	inline X_Wobble			XWobble;

	inline std::vector<Vertex_Shader*> PtrList =
	{
		&Default,
		&FloatObject,
		&PulseObject,
		&XWobble
	};
}