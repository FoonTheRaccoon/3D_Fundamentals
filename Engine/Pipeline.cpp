#include "Pipeline.h"
#include <cmath>
#include <execution>

void Pipeline::Update()
{
	for (auto& obj : objs)
	{
		//Init Tri list.
		static std::vector<Triangle> triangles;
		triangles = obj->GetTriangles();

		//Set Rotation matrix.
		const Mat3 rot = GetRot(obj->GetTheta());

		//Apply rotation and set cull flags.
		std::for_each(std::execution::par, triangles.begin(), triangles.end(), [&](Triangle& tri)
			{
				VertexTransformer(rot, obj->GetPos(), tri);
				TriangleAssembler(tri);
			});

		//Cull the tris (Duh)
		Cull(triangles);

		//Transform and draw the Tris
		std::for_each(std::execution::par, triangles.begin(), triangles.end(), [&](Triangle& tri)
			{
				PerspecScreenTransform(tri);
				TriangleRasterizer(tri, obj->GetTexture());
			});

		//Clear Cache
		triangles.clear();
	}
	
}

void Pipeline::VertexTransformer(const Mat3& rot,const Vec3& pos, Triangle& tri)
{
	//Apply Rot + Offset
	tri.v0.pos *= rot;
	tri.v1.pos *= rot;
	tri.v2.pos *= rot;
	tri.v0.pos += pos;
	tri.v1.pos += pos;
	tri.v2.pos += pos;
}

void Pipeline::TriangleAssembler(Triangle& tri)
{
	//Apply back face culling flags
	tri.cullFlag = (tri.v1.pos - tri.v0.pos).X(tri.v2.pos - tri.v0.pos) * tri.v0.pos >= 0.0f; //Cross two vectors in a tri to get perpendicular vec, then compare to veiwport space vector
}

void Pipeline::Cull(std::vector<Triangle>& triangles)
{
	//Check for cull flags and erase
	triangles.erase(std::remove_if(std::execution::par, triangles.begin(), triangles.end(), [](Triangle& tri) {return tri.cullFlag; }), triangles.end());
}

void Pipeline::PerspecScreenTransform(Triangle& tri)
{
	//Transform to screen perpective.
	pst.Transform(tri.v0.pos);
	pst.Transform(tri.v1.pos);
	pst.Transform(tri.v2.pos);
}


Mat3 Pipeline::GetRot(const Vec3& theta)
{
	//Set Rot
	return Mat3(
		Mat3::RotationX(theta.x) *
		Mat3::RotationY(theta.y) *
		Mat3::RotationZ(theta.z));
}

void Pipeline::TriangleRasterizer(const Triangle& tri, Surface& texture)
{
	//Ptr creation for swaps.
	const Vertex* p0 = &tri.v0;
	const Vertex* p1 = &tri.v1;
	const Vertex* p2 = &tri.v2;

	//Sort points by y.
	if (p1->pos.y < p0->pos.y) { std::swap(p1, p0); };
	if (p2->pos.y < p1->pos.y) { std::swap(p2, p1); };
	if (p1->pos.y < p0->pos.y) { std::swap(p1, p0); };

	//Check for natural flats
	if (p0->pos.y == p1->pos.y) //Flat top check
	{
		if (p1->pos.x < p0->pos.x) { std::swap(p1, p0); };
		DrawFlatTopTriangle(*p0, *p1, *p2, texture);
	}
	else if (p2->pos.y == p1->pos.y) //Flat bottom Check
	{
		if (p2->pos.x < p1->pos.x) { std::swap(p1, p2); };
		DrawFlatBottomTriangle(*p0, *p1, *p2, texture);
	}
	else //General Triangle
	{
		//v0 = top, v1 = mid, v2 = bottom

		//Calculate mid point ratio within top and bottom points
		const float alpha = (p1->pos.y - p0->pos.y) / (p2->pos.y - p0->pos.y);

		const Vertex mid = p0->InterpolateTo(*p2, alpha);

		if (mid.pos.x < p1->pos.x) // Major Left
		{
			DrawFlatBottomTriangle(*p0, mid, *p1, texture);
			DrawFlatTopTriangle(mid, *p1, *p2, texture);
		}
		else //Major Right
		{
			DrawFlatBottomTriangle(*p0, *p1, mid, texture);
			DrawFlatTopTriangle(*p1, mid, *p2, texture);
		}
	}
}

void Pipeline::DrawFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture)
{
	//v0 top left, v1 top right, v2 bottom point

	Vertex R_line = v1; //Left line is the same formula for both triangles

	const float alpha = (v2.pos.y - v0.pos.y);

	const Vertex dL = (v2 - v0) / alpha; //Change in x per y (inverse slope) of left line.
	const Vertex dR = (v2 - v1) / alpha; //Same but for right.

	DrawFlatTriangle(v0, v1, v2, texture, dL, dR, R_line);
}

void Pipeline::DrawFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture)
{
	//v0 top point, v1 bottom left, v2 bottom right
	
	Vertex R_line = v0;

	const float alpha = (v2.pos.y - v0.pos.y);

	const Vertex dL = (v1 - v0) / alpha; //Change in x per y (inverse slope) of left line.
	const Vertex dR = (v2 - v0) / alpha; //Same but for right.

	DrawFlatTriangle(v0, v1, v2, texture, dL, dR, R_line);
}

void Pipeline::DrawFlatTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture, const Vertex& dL, const Vertex& dR, Vertex& R_line)
{
	//Set Texture Bounds
	const float tex_width = float(texture.GetWidth());
	const float tex_height = float(texture.GetHeight());
	const float tex_clamp_x = tex_width - 1.0f;
	const float tex_clamp_y = tex_height - 1.0f;

	//Add Right Side Line
	Vertex L_line = v0;

	//Set YBounds
	const int yStart = (int)ceilf(v0.pos.y - 0.5f);
	const int yEnd = (int)ceilf(v2.pos.y - 0.5f);

	//Do Prestep
	L_line += dL * (float(yStart) + 0.5f - v0.pos.y);
	R_line += dR * (float(yStart) + 0.5f - v0.pos.y);

	for (int iy = yStart; iy < yEnd; ++iy, L_line += dL, R_line += dR)
	{
		const int xStart = (int)ceilf(L_line.pos.x - 0.5f);
		const int xEnd = (int)ceilf(R_line.pos.x - 0.5f);

		const Vec2 c_incr = (R_line.texCor - L_line.texCor) / (R_line.pos.x - L_line.pos.x);
		Vec2 C = L_line.texCor + c_incr * (float(xStart) + 0.5f - L_line.pos.x);

		for (int ix = xStart; ix < xEnd; ++ix, C += c_incr)
		{
			gfx.PutPixel(ix, iy, texture.GetPixel((int)std::fmod(C.x * tex_width, tex_clamp_x), (int)std::fmod(C.y * tex_height, tex_clamp_y)));
		}
	}
}
