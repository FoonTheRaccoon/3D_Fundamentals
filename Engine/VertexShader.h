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
		time += dt;
	}
	void ResetTime()
	{
		time = 0.0f;
	}
	float time = 0.0f;
};

class Float_Object : public Vertex_Shader
{
public:
	Triangle Effect(Triangle& tri) override
	{
		tri.v0.pos.y = tri.v0.pos.y + (sin(time) / 6);
		tri.v1.pos.y = tri.v1.pos.y + (sin(time) / 6);
		tri.v2.pos.y = tri.v2.pos.y + (sin(time) / 6);

		return tri;
	}
};

class Pulse_Object : public Vertex_Shader
{
public:
	Triangle Effect(Triangle& tri) override
	{
		tri.v0.pos.y = tri.v0.pos.y + (tri.v0.pos.y * sin(time) / 6);
		tri.v1.pos.y = tri.v1.pos.y + (tri.v1.pos.y * sin(time) / 6);
		tri.v2.pos.y = tri.v2.pos.y + (tri.v2.pos.y * sin(time) / 6);

		tri.v0.pos.x = tri.v0.pos.x + (tri.v0.pos.x * sin(time) / 6);
		tri.v1.pos.x = tri.v1.pos.x + (tri.v1.pos.x * sin(time) / 6);
		tri.v2.pos.x = tri.v2.pos.x + (tri.v2.pos.x * sin(time) / 6);

		return tri;
	}
};

class X_Wobble : public Vertex_Shader
{
public:
	Triangle Effect(Triangle& tri) override
	{
		tri.v0.pos.x = tri.v0.pos.x + (sin(time * tri.v0.pos.y) / 6);
		tri.v1.pos.x = tri.v1.pos.x + (sin(time * tri.v1.pos.y) / 6);
		tri.v2.pos.x = tri.v2.pos.x + (sin(time * tri.v2.pos.y) / 6);

		return tri;
	}
};


namespace VertexShader
{
	inline Vertex_Shader	Default;
	inline Float_Object		FloatObject;
	inline Pulse_Object		PulseObject;
	inline X_Wobble			XWobble;
}