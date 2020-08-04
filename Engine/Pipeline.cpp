#include "Pipeline.h"
#include <cmath>
#include <execution>

void Pipeline::Update(float dt)
{
	//Set the ZBuffer for the frame
	zbuffer.Clear();

	//Increment Shader times
	ps->IncrementTime(dt);
	vs->IncrementTime(dt);

	for (auto& obj : objs)
	{
		//Point Pixel/Vertex Shaders to relevent object data.
		ps->PointToTexture(obj->GetTexturePtr());

		//Init Tri list.
		static std::vector<Triangle> triangles;
		triangles = obj->GetTriangles();

		//Set Rotation matrix/pos
		static Mat3 rot;
		rot = GetRot(obj->GetTheta());
		static Vec3 pos;
		pos = obj->GetPos();

		//Start of the pipeline, 
		std::for_each(std::execution::par, triangles.begin(), triangles.end(), [&](Triangle& tri)
			{
				//Send off to transform with obj rotationand pos
				VertexTransformer(rot, pos, tri);
			});

		//Clear Cache
		triangles.clear();
	}
	
}

Mat3 Pipeline::GetRot(const Vec3& theta)
{
	//Set Rot
	return Mat3(
		Mat3::RotationX(theta.x) *
		Mat3::RotationY(theta.y) *
		Mat3::RotationZ(theta.z));
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

	//Send off to the Vertex Shader
	vs->Effect(tri);

	//Send To get culled
	TriangleAssembler(tri);
}

void Pipeline::TriangleAssembler(Triangle& tri)
{
	//Apply back face culling flags
	if (!((tri.v1.pos - tri.v0.pos).X(tri.v2.pos - tri.v0.pos) * tri.v0.pos >= 0.0f)) //Cross two vectors in a tri to get perpendicular vec, then compare to veiwport space vector
		PerspecScreenTransform(tri); //Send To get Transforms into screen space
}

void Pipeline::PerspecScreenTransform(Triangle& tri)
{
	//Transform to screen perpective.
	pst.Transform(tri.v0);
	pst.Transform(tri.v1);
	pst.Transform(tri.v2);

	//Send To Draw The Triangle.
	TriangleRasterizer(tri);
}

void Pipeline::TriangleRasterizer(const Triangle& tri)
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
		DrawFlatTopTriangle(tri, *p0, *p1, *p2);
	}
	else if (p2->pos.y == p1->pos.y) //Flat bottom Check
	{
		if (p2->pos.x < p1->pos.x) { std::swap(p1, p2); };
		DrawFlatBottomTriangle(tri, *p0, *p1, *p2);
	}
	else //General Triangle
	{
		//v0 = top, v1 = mid, v2 = bottom

		//Calculate mid point ratio within top and bottom points
		const float alpha = (p1->pos.y - p0->pos.y) / (p2->pos.y - p0->pos.y);

		const Vertex mid = p0->InterpolateTo(*p2, alpha);

		if (mid.pos.x < p1->pos.x) // Major Left
		{
			DrawFlatBottomTriangle(tri, *p0, mid, *p1);
			DrawFlatTopTriangle(tri, mid, *p1, *p2);
		}
		else //Major Right
		{
			DrawFlatBottomTriangle(tri, *p0, *p1, mid);
			DrawFlatTopTriangle(tri, *p1, mid, *p2);
		}
	}
}

void Pipeline::DrawFlatTopTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	//v0 top left, v1 top right, v2 bottom point

	Vertex R_line = v1; //Left line is the same formula for both triangles

	const float alpha = (v2.pos.y - v0.pos.y);

	const Vertex dL = (v2 - v0) / alpha; //Change in x per y (inverse slope) of left line.
	const Vertex dR = (v2 - v1) / alpha; //Same but for right.

	DrawFlatTriangle(tri, v0, v1, v2, dL, dR, R_line);
}

void Pipeline::DrawFlatBottomTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	//v0 top point, v1 bottom left, v2 bottom right
	
	Vertex R_line = v0;

	const float alpha = (v2.pos.y - v0.pos.y);

	const Vertex dL = (v1 - v0) / alpha; //Change in x per y (inverse slope) of left line.
	const Vertex dR = (v2 - v0) / alpha; //Same but for right.

	DrawFlatTriangle(tri, v0, v1, v2, dL, dR, R_line);
}

void Pipeline::DrawFlatTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& dL, const Vertex& dR, Vertex& R_line)
{
	//Add Left Side Line
	Vertex L_line = v0;

	//Set YBounds
	const int yStart = (int)ceilf(v0.pos.y - 0.5f);
	const int yEnd = (int)ceilf(v2.pos.y - 0.5f);

	//Do Prestep
	L_line += dL * (float(yStart) + 0.5f - v0.pos.y);
	R_line += dR * (float(yStart) + 0.5f - v0.pos.y);

	for (int y = yStart; y < yEnd; ++y, L_line += dL, R_line += dR)
	{
		//Set Tri x start/end
		const int xStart = (int)ceilf(L_line.pos.x - 0.5f);
		const int xEnd = (int)ceilf(R_line.pos.x - 0.5f);

		//Set Texture iterartor
		Vertex Tex_Line = L_line;

		//Use pos x difference to get texture incrament.
		const float tex_dx = (R_line.pos.x - L_line.pos.x);
		const Vertex tex_incr = (R_line - L_line) / tex_dx;

		//Do texture read prestep.
		Tex_Line += tex_incr * (float(xStart) + 0.5f - L_line.pos.x);

		for (int x = xStart; x < xEnd; ++x, Tex_Line += tex_incr)
		{
			const float z = 1.0f / Tex_Line.pos.z;
			if (zbuffer.TestAndSet(x, y, z))
			{
				const Vertex pixel = Tex_Line * z;
				gfx.PutPixel(x, y, ps->Effect(tri, pixel));
			}
		}
	}
}
