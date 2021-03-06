#include "Pipeline.h"
#include <cmath>
#include <execution>

void Pipeline::Update(float dt)
{
	//Set the ZBuffer for the frame
	zbuffer.Clear();

	//Point to light list for drawing
	ps->PointToLightList(&lights);

	//Increment Shader times
	ps->IncrementTime(dt);
	vs->IncrementTime(dt);

	if (revealLights)
	{
		//Set all lights to draw as white and save old ps ptr.
		auto shader = ps;
		ps = &PixelShader::SolidWhite;

		for (auto& light : lights)
		{
			

			//Point Pixel/Vertex Shaders to relevent object data.
			ps->PointToTexture(light->GetTexturePtr());

			//Init Tri list.
			static std::vector<Triangle> lightTri;
			lightTri = light->GetTriangles();

			//Set Rotation matrix/pos
			static Mat3 lightrot;
			lightrot = Mat3::Identity();
			static Vec3 lightpos;
			lightpos = light->GetPos();


			//Start of the pipeline
			std::for_each(std::execution::par, lightTri.begin(), lightTri.end(), [&](Triangle& tri)
				{
					//Send off to transform with obj rotationand pos
					VertexTransformer(lightrot, lightpos, tri);
				});

			//Clear Cache 
			lightTri.clear();
		}
		//Set back to original ps ptr
		ps = shader;
	}

	for (auto& obj : objs)
	{
		//Point Pixel/Vertex Shaders to relevent object data.
		ps->PointToTexture(obj->GetTexturePtr());

		//Init Tri list.
		static std::vector<Triangle> triangles;
		triangles = obj->GetTriangles();

		//Set Rotation matrix/pos
		static Mat3 rot;
		rot = Mat3::GetRotation(obj->GetTheta());
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

void Pipeline::VertexTransformer(const Mat3& rot,const Vec3& pos, Triangle& tri)
{
	//Apply Rot + Offset
	tri.TransformTriangle(rot, pos);

	//Send off to the Vertex Shader
	vs->Effect(tri);

	//Send To get culled
	TriangleClipper(tri);
}

void Pipeline::TriangleClipper(Triangle& tri)
{
	// cull tests
	if (tri.v0.pos.x > tri.v0.pos.w &&
		tri.v1.pos.x > tri.v1.pos.w &&
		tri.v2.pos.x > tri.v2.pos.w)
	{
		return;
	}
	if (tri.v0.pos.x < -tri.v0.pos.w &&
		tri.v1.pos.x < -tri.v1.pos.w &&
		tri.v2.pos.x < -tri.v2.pos.w)
	{
		return;
	}
	if (tri.v0.pos.y > tri.v0.pos.w &&
		tri.v1.pos.y > tri.v1.pos.w &&
		tri.v2.pos.y > tri.v2.pos.w)
	{
		return;
	}
	if (tri.v0.pos.y < -tri.v0.pos.w &&
		tri.v1.pos.y < -tri.v1.pos.w &&
		tri.v2.pos.y < -tri.v2.pos.w)
	{
		return;
	}
	if (tri.v0.pos.z < 0.0f &&
		tri.v1.pos.z < 0.0f &&
		tri.v2.pos.z < 0.0f)
	{
		return;
	}

	// clipping routines
	const auto Clip1 = [this](Vertex& v0, Vertex& v1, Vertex& v2)
	{
		// calculate alpha values for getting adjusted vertices
		const float alphaA = (-v0.pos.z) / (v1.pos.z - v0.pos.z);
		const float alphaB = (-v0.pos.z) / (v2.pos.z - v0.pos.z);
		// interpolate to get v0a and v0b
		const Vertex v0a = v0.InterpolateTo(v1, alphaA);
		const Vertex v0b = v0.InterpolateTo(v2, alphaB);
		// draw triangles
		TriangleAssembler(Triangle{ v0a, v1, v2 , Color(v2.color)});
		TriangleAssembler(Triangle{ v0b, v0a, v2, Color(v2.color)});
	};
	const auto Clip2 = [this](Vertex& v0, Vertex& v1, Vertex& v2)
	{
		// calculate alpha values for getting adjusted vertices
		const float alpha0 = (-v0.pos.z) / (v2.pos.z - v0.pos.z);
		const float alpha1 = (-v1.pos.z) / (v2.pos.z - v1.pos.z);
		// interpolate to get v0a and v0b
		v0 = v0.InterpolateTo(v2, alpha0);
		v1 = v1.InterpolateTo(v2, alpha1);
		// draw triangles
		TriangleAssembler(Triangle{ v0, v1, v2, Color(v2.color)});
	};
	
	// near clipping tests
	if (tri.v0.pos.z < 0.0f)
	{
		if (tri.v1.pos.z < 0.0f)
		{
			Clip2(tri.v0, tri.v1, tri.v2);
		}
		else if (tri.v2.pos.z < 0.0f)
		{
			Clip2(tri.v0, tri.v2, tri.v1);
		}
		else
		{
			Clip1(tri.v0, tri.v1, tri.v2);
		}
	}
	else if (tri.v1.pos.z < 0.0f)
	{
		if (tri.v2.pos.z < 0.0f)
		{
			Clip2(tri.v1, tri.v2, tri.v0);
		}
		else
		{
			Clip1(tri.v1, tri.v0, tri.v2);
		}
	}
	else if (tri.v2.pos.z < 0.0f)
	{
		Clip1(tri.v2, tri.v0, tri.v1);
	}
	else // no near clipping necessary
	{
		TriangleAssembler(tri);
	}
}

void Pipeline::TriangleAssembler(Triangle& tri)
{
	//Apply back face culling flags
	if (!(tri.faceNorm * tri.v0.pos >= 0.0f)) //Cross two vectors in a tri to get perpendicular vec, then compare to veiwport space vector
		PerspecScreenTransform(tri); //Send To get Transforms into screen space
}

void Pipeline::PerspecScreenTransform(Triangle& tri)
{
	//Transform to screen perpective.
	pst.TransformTri(tri);

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
	const int yStart = std::max((int)ceilf(v0.pos.y - 0.5f), 0);
	const int yEnd = std::min((int)ceilf(v2.pos.y - 0.5f), (int)Graphics::ScreenHeight - 1);

	//Do Prestep
	L_line += dL * (float(yStart) + 0.5f - v0.pos.y);
	R_line += dR * (float(yStart) + 0.5f - v0.pos.y);

	for (int y = yStart; y < yEnd; ++y, L_line += dL, R_line += dR) 
	{
		//Set Tri x start/end
		const int xStart = std::max((int)ceilf(L_line.pos.x - 0.5f), 0);
		const int xEnd = std::min((int)ceilf(R_line.pos.x - 0.5f), (int)Graphics::ScreenWidth - 1);

		//Set Texture iterator starting point
		Vertex Tex_Line = L_line;

		//Use pos x difference to get texture incrament.
		const float tex_dx = (R_line.pos.x - L_line.pos.x);
		const Vertex tex_incr = (R_line - L_line) / tex_dx;

		//Do texture read prestep.
		Tex_Line += tex_incr * (float(xStart) + 0.5f - L_line.pos.x);

		for (int x = xStart; x < xEnd; ++x, Tex_Line += tex_incr)
		{
			if (zbuffer.TestAndSet(x, y, Tex_Line.pos.z) && (Tex_Line.worldPos.z > 0.01f))
			{
				const Vertex pixel = Vertex::PixelReadyToDraw(Tex_Line, Tex_Line.pos.w);
				gfx.PutPixel(x, y, ps->Effect(tri, pixel));
			}
		}
	}
}
