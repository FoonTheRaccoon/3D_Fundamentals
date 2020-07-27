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

void Object::DrawTextureless(Graphics& gfx, PerspectiveScreenTransformer& pst)
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

void Object::DrawTextured(Graphics& gfx, PerspectiveScreenTransformer& pst)
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
	
			gfx.DrawTriangleTex(
				triangles.verts[triangles.indices[i * 3]],
				triangles.verts[triangles.indices[i * 3 + 1]],
				triangles.verts[triangles.indices[i * 3 + 2]],
				model.texture);
		}
	}
}

void Object::TransformVerts(IndexedTriangleList& triangles)
{
	//Set Rot
	const Mat3 rot =
		Mat3::RotationX(theta.x) *
		Mat3::RotationY(theta.y) *
		Mat3::RotationZ(theta.z);
	//Apply Rot + Offset
	for (auto& v : triangles.verts)
	{
		v.pos *= rot;
		v.pos += pos;
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
