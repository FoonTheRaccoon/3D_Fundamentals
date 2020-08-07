#pragma once
#include "Mat3.h"
#include "Vec3.h"
#include "Triangle.h"
#include "MainWindow.h"

class Light
{
public:
	void Update(MainWindow& wnd, float dt)
	{
		if (wnd.kbd.KeyIsPressed('U'))
		{
			direction.x = wrap_angle(direction.x + PI * dt);
		}
		if (wnd.kbd.KeyIsPressed('I'))
		{
			direction.y = wrap_angle(direction.y + PI * dt);
		}
		if (wnd.kbd.KeyIsPressed('O'))
		{
			direction.z = wrap_angle(direction.z + PI * dt);
		}
		if (wnd.kbd.KeyIsPressed('J'))
		{
			direction.x = wrap_angle(direction.x - PI * dt);
		}
		if (wnd.kbd.KeyIsPressed('K'))
		{
			direction.y = wrap_angle(direction.y - PI * dt);
		}
		if (wnd.kbd.KeyIsPressed('L'))
		{
			direction.z = wrap_angle(direction.z - PI * dt);
		}
		direction.Normalize();
	}
	void SetWorldLightShadingBias(Triangle& tri)
	{

		float result = ((-tri.faceNorm) * direction) * intensity;

		result = std::clamp(result, ambient, diffuse);

		tri.lightBias = result;
	}


	float intensity = 1.0f;
	float ambient = 0.05f;
	float diffuse = 0.9f;
	Vec3 direction = { 1.0f, 1.0f , 1.0f};
	
};

inline Light worldLight;