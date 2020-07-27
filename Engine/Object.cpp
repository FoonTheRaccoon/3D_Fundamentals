#include "Object.h"

void Object::Update(float dt)
{
	if (kbd.KeyIsPressed('Q'))
	{
		theta.x = wrap_angle(theta.x + dTheta * dt);
	}
	if (kbd.KeyIsPressed('W'))
	{
		theta.y = wrap_angle(theta.y + dTheta * dt);
	}
	if (kbd.KeyIsPressed('E'))
	{
		theta.z = wrap_angle(theta.z + dTheta * dt);
	}
	if (kbd.KeyIsPressed('A'))
	{
		theta.x = wrap_angle(theta.x - dTheta * dt);
	}
	if (kbd.KeyIsPressed('S'))
	{
		theta.y = wrap_angle(theta.y - dTheta * dt);
	}
	if (kbd.KeyIsPressed('D'))
	{
		theta.z = wrap_angle(theta.z - dTheta * dt);
	}
	if (kbd.KeyIsPressed('R'))
	{
		pos.z += 2.0f * dt;
	}
	if (kbd.KeyIsPressed('F'))
	{
		pos.z -= 2.0f * dt;
	}
}

