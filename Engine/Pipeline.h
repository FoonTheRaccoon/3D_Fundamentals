#pragma once
#include "Object.h"
#include "Graphics.h"
#include "PerspectiveScreenTransformer.h"
#include "Triangle.h"
#include "PixelShader.h"
#include "ZBuffer.h"

class Pipeline
{
public:
	Pipeline(Graphics& gfx)
		: 
		gfx(gfx), 
		ps(&Effect::Default), 
		zbuffer(Graphics::ScreenWidth, Graphics::ScreenHeight)
	{}
	void AddObject(Object* obj)
	{
		objs.emplace_back(obj);
	}
	//ShaderChanger
	void SetPixelShader(PixelShader* ps_in)
	{
		ps = ps_in;
	}
	void Update();
private:
	//Main pipeline
	void VertexTransformer(const Mat3& rot, const Vec3& pos, Triangle& tri);
	void TriangleAssembler(Triangle& tri);
	void Cull(std::vector<Triangle>& triangles);
	void PerspecScreenTransform(Triangle& tri);
	//Pipeline helper Functions
	Mat3 GetRot(const Vec3& theta);
	//Triangle Rasterizer Functions
	void TriangleRasterizer(const Triangle& tri, Surface& texture);
	void DrawFlatTopTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture);
	void DrawFlatBottomTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture);
	void DrawFlatTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface& texture, const Vertex& dL, const Vertex& dR, Vertex& R_line);
	
private:
	std::vector<Object*> objs;
	Graphics& gfx;
	PerspectiveScreenTransformer pst;
	PixelShader* ps;
	ZBuffer zbuffer;
};

