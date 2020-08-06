#include "Object.h"

void Object::Update(MainWindow& wnd, float dt)
{
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		theta.x = wrap_angle(theta.x + PI * dt);
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		theta.y = wrap_angle(theta.y + PI * dt);
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		theta.z = wrap_angle(theta.z + PI * dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		theta.x = wrap_angle(theta.x - PI * dt);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		theta.y = wrap_angle(theta.y - PI * dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		theta.z = wrap_angle(theta.z - PI * dt);
	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		pos.z += 2.0f * dt;
	}
	if (wnd.kbd.KeyIsPressed('F'))
	{
		pos.z -= 2.0f * dt;
	}
}

