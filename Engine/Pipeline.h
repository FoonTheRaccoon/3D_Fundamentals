#pragma once
#include "Object.h"
#include "Graphics.h"
#include "PerspectiveScreenTransformer.h"
#include "Triangle.h"

class Pipeline
{
public:
	Pipeline(Graphics& gfx)
		: gfx(gfx)
	{}
	void AddObject(Object& obj)
	{
		objs.emplace_back(obj, Triangle::MakeTriangleList(obj.GetTriangles()));
	}
	void Update();
private:
	void VertexTransformer(const Vec3& theta, const Vec3& pos, std::vector<Triangle>& triangles);
	void TriangleAssembler(std::vector<Triangle>& triangles);
	void PerspecScreenTransform(std::vector<Triangle>& triangles);
	void TriangleRasterizer(std::vector<Triangle>& triangles, Surface& texture);
	//Triangle Rasterizer Functions
	void DrawTriangle(const Triangle& tri, Surface& texture);
	void DrawFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture);
	void DrawFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture);
	void DrawFlatTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture, const Vertex& dL, const Vertex& dR, Vertex& R_line);
private:
	std::vector<std::pair<Object&,const std::vector<Triangle>>> objs;
	Graphics& gfx;
	PerspectiveScreenTransformer pst;
};

