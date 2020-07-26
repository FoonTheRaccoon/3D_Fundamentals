#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat3.h"
#include "MainWindow.h"
#include "Graphics.h"
#include "PubeScreenTransformer.h"
#include <vector>
#include "IndexedLineList.h"
#include "IndexedTriangleList.h"

class Object
{
public:
	Object(Keyboard& kbd, Mouse& mouse)
		: kbd(kbd), mouse(mouse)
	{}
	void Update(float dt)
	{
		if (kbd.KeyIsPressed('Q'))
		{
			theta_x = wrap_angle(theta_x + dTheta * dt);
		}
		if (kbd.KeyIsPressed('W'))
		{
			theta_y = wrap_angle(theta_y + dTheta * dt);
		}
		if (kbd.KeyIsPressed('E'))
		{
			theta_z = wrap_angle(theta_z + dTheta * dt);
		}
		if (kbd.KeyIsPressed('A'))
		{
			theta_x = wrap_angle(theta_x - dTheta * dt);
		}
		if (kbd.KeyIsPressed('S'))
		{
			theta_y = wrap_angle(theta_y - dTheta * dt);
		}
		if (kbd.KeyIsPressed('D'))
		{
			theta_z = wrap_angle(theta_z - dTheta * dt);
		}
		if (kbd.KeyIsPressed('R'))
		{
			offset_z += 2.0f * dt;
		}
		if (kbd.KeyIsPressed('F'))
		{
			offset_z -= 2.0f * dt;
		}
	}
	void Draw(Graphics& gfx, PubeScreenTransformer& pst, Object& obj)
	{
		//Get Tri's
		auto triangles = obj.GetTriangles();
		//Set Rot
		const Mat3 rot =
			Mat3::RotationX(theta_x) *
			Mat3::RotationY(theta_y) *
			Mat3::RotationZ(theta_z);
		//Apply Rot + Offset
		for (auto& v : triangles.vertices)
		{
			v *= rot;
			v += { 0.0f, 0.0f, offset_z };
		}

		//Apply back face culling flags
		for (int i = 0; i < (triangles.indices.size() / 3); ++i)
		{
			const Vec3& v0 = triangles.vertices[triangles.indices[i * 3]];
			const Vec3& v1 = triangles.vertices[triangles.indices[i * 3 + 1]];
			const Vec3& v2 = triangles.vertices[triangles.indices[i * 3 + 2]];
			triangles.cullFlags[i] = (v1 - v0).X(v2 - v0) * v0 >= 0.0f; //Cross two vectors in a tri to get perpendicular vec, then compare to veiwport space vector
		}


		//Apply Screen space transform
		for (auto& v : triangles.vertices)
		{
			pst.Transform(v);
		}

		//Draw verts
		for (int i = 0; i < triangles.indices.size() / 3; ++i)
		{
			if (!triangles.cullFlags[i])
			{
				gfx.DrawTriangle(
					triangles.vertices[triangles.indices[i * 3]],
					triangles.vertices[triangles.indices[i * 3 + 1]],
					triangles.vertices[triangles.indices[i * 3 + 2]], colors[i]);
			}
		}
	}
	virtual IndexedTriangleList GetTriangles() const = 0;
protected:
	static constexpr float dTheta = PI;
	float offset_z = 2.0f;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
	Keyboard& kbd;
	Mouse& mouse;
	std::vector<Vec3> vertices;


	const Color colors[12] = {
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray,
		Colors::Green,
		Colors::LightGray,
		Colors::Magenta,
		Colors::Red,
		Colors::White,
		Colors::Yellow,
		Colors::MakeRGB(100u, 0u,100u),
		Colors::MakeRGB(200u,200u, 0u),
		Colors::MakeRGB(100u,200u, 255u)
	};
};