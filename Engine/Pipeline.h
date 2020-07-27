#pragma once
#include "Object.h"
#include "Graphics.h"
#include "PerspectiveScreenTransformer.h"

class Pipeline
{
public:
	Pipeline(Graphics& gfx)
		: gfx(gfx)
	{}
	void AddObject(Object& obj)
	{
		objs.emplace_back(obj);
	}
	void Update();
	void VertexTransformer(const Vec3& theta, const Vec3& pos, IndexedTriangleList& triangles);
	void TriangleAssembler(IndexedTriangleList& triangles);
	void PerspecScreenTransform();
	void TriangleRasterizer();

private:
	std::vector<Object&> objs;
	Graphics& gfx;
	PerspectiveScreenTransformer pst;

};

