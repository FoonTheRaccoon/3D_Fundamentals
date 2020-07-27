#include "Pipeline.h"

void Pipeline::Update()
{
	for (auto& obj : objs)
	{
		auto triangles = obj.GetTriangles();
		VertexTransformer(obj.GetTheta(), obj.GetPos(), triangles);

	}
}

void Pipeline::VertexTransformer(const Vec3& theta, const Vec3& pos, IndexedTriangleList& triangles)
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

void Pipeline::TriangleAssembler(IndexedTriangleList& triangles)
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

void Pipeline::PerspecScreenTransform()
{
}

void Pipeline::TriangleRasterizer()
{
}
