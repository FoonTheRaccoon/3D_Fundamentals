#include "Object.h"

void Object::Update(float dt)
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

void Object::DrawTextureless(Graphics& gfx, PubeScreenTransformer& pst)
{
	//Get Tri's
	auto triangles = GetTriangles();
	
	TransformVerts(triangles);

	SetCullFlags(triangles);
	
	//Apply Screen space transform
	for (auto& v : triangles.verts)
	{
		pst.Transform(v.pos);
	}

	//Draw verts
	for (int i = 0; i < triangles.indices.size() / 3; ++i)
	{
		if (!triangles.cullFlags[i])
		{

			gfx.DrawTriangle(
				triangles.verts[triangles.indices[i * 3]].pos,
				triangles.verts[triangles.indices[i * 3 + 1]].pos,
				triangles.verts[triangles.indices[i * 3 + 2]].pos, 
				colors[i % 12]);
		}
	}
}

void Object::DrawTextured(Graphics& gfx, PubeScreenTransformer& pst)
{
	////Get Tri's
	//auto triangles = GetTriangles();
	//
	//TransformVerts(triangles);
	//
	//SetCullFlags(triangles);
	//
	////Apply Screen space transform
	//for (auto& v : triangles.pos)
	//{
	//	pst.Transform(v);
	//}
	//
	////Draw verts
	//for (int i = 0; i < triangles.indices.size() / 3; ++i)
	//{
	//	if (!triangles.cullFlags[i])
	//	{
	//
	//		gfx.DrawTriangleTex(
	//			triangles[triangles.indices[i * 3]],
	//			triangles[triangles.indices[i * 3 + 1]],
	//			triangles[triangles.indices[i * 3 + 2]], texture);
	//	}
	//}
}

void Object::TransformVerts(IndexedTriangleList& triangles)
{
	//Set Rot
	const Mat3 rot =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);
	//Apply Rot + Offset
	for (auto& v : triangles.verts)
	{
		v.pos *= rot;
		v.pos += { 0.0f, 0.0f, offset_z };
	}
}

void Object::SetCullFlags(IndexedTriangleList& triangles)
{
	//Apply back face culling flags
	for (int i = 0; i < (triangles.indices.size() / 3); ++i)
	{
		const Vec3& v0 = triangles.verts[triangles.indices[i * 3]].pos;
		const Vec3& v1 = triangles.verts[triangles.indices[i * 3 + 1]].pos;
		const Vec3& v2 = triangles.verts[triangles.indices[i * 3 + 2]].pos;
		triangles.cullFlags[i] = (v1 - v0).X(v2 - v0) * v0 >= 0.0f; //Cross two vectors in a tri to get perpendicular vec, then compare to veiwport space vector
	}
}
