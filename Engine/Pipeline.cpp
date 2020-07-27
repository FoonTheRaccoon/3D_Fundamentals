#include "Pipeline.h"

void Pipeline::Update()
{
	for (auto& obj : objs)
	{
		auto triangles = obj.second;
		VertexTransformer(obj.first.GetTheta(), obj.first.GetPos(), triangles);
		TriangleAssembler(triangles);
		PerspecScreenTransform(triangles);
		TriangleRasterizer(triangles, obj.first.GetTexture());
	}
}

void Pipeline::VertexTransformer(const Vec3& theta, const Vec3& pos, std::vector<Triangle>& triangles)
{
	//Set Rot
	const Mat3 rot =
		Mat3::RotationX(theta.x) *
		Mat3::RotationY(theta.y) *
		Mat3::RotationZ(theta.z);
	//Apply Rot + Offset
	for (auto& tri : triangles)
	{
		tri.v0.pos *= rot;
		tri.v1.pos *= rot;
		tri.v2.pos *= rot;
		tri.v0.pos += pos;
		tri.v1.pos += pos;
		tri.v2.pos += pos;
	}
}

void Pipeline::TriangleAssembler(std::vector<Triangle>& triangles)
{
	//Apply back face culling flags
	for (auto& tri : triangles)
	{
		tri.cullFlag = (tri.v1.pos - tri.v0.pos).X(tri.v2.pos - tri.v0.pos) * tri.v0.pos >= 0.0f; //Cross two vectors in a tri to get perpendicular vec, then compare to veiwport space vector
	}
	
	triangles.erase(std::remove_if(triangles.begin(), triangles.end(), [](Triangle& tri) {return tri.cullFlag; }), triangles.end());

}

void Pipeline::PerspecScreenTransform(std::vector<Triangle>& triangles)
{
	for (auto& tri : triangles)
	{
		pst.Transform(tri.v0.pos);
		pst.Transform(tri.v1.pos);
		pst.Transform(tri.v2.pos);
	}
}

void Pipeline::TriangleRasterizer(std::vector<Triangle>& triangles, Surface& texture)
{
	for (auto& tri : triangles)
	{
		gfx.DrawTriangleTex(tri.v0, tri.v1, tri.v2, texture);
	}
}
