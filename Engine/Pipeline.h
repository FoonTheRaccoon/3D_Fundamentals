#pragma once
#include "Object.h"
#include "Graphics.h"
#include "PerspectiveScreenTransformer.h"
#include "Triangle.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "ZBuffer.h"

class Pipeline
{
public:
	Pipeline(Graphics& gfx)
		: 
		gfx(gfx), 
		ps(&PixelShader::Default),
		vs(&VertexShader::Default),
		zbuffer(Graphics::ScreenWidth, Graphics::ScreenHeight)
	{}
	void AddObject(Object* obj)
	{
		objs.emplace_back(obj);
	}
	void DropObject(Object* obj)
	{
		auto removed_obj = std::find(objs.begin(), objs.end(), obj);

		if (removed_obj != objs.end())
			objs.erase(removed_obj);
	}
	//ShaderChanger
	void SetPixelShader(Pixel_Shader* ps_in)
	{
		ps = ps_in;
		ps->ResetTime();
	}
	void SetVertexShader(Vertex_Shader* vs_in)
	{
		vs = vs_in;
		vs->ResetTime();
	}
	void Update(float dt);
private:
	//Main pipeline
	void VertexTransformer(const Mat3& rot, const Vec3& pos, Triangle& tri);
	void TriangleAssembler(Triangle& tri);
	void PerspecScreenTransform(Triangle& tri);
	//Triangle Rasterizer Functions
	void TriangleRasterizer(const Triangle& tri);
	void DrawFlatTopTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void DrawFlatBottomTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void DrawFlatTriangle(const Triangle& tri, const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& dL, const Vertex& dR, Vertex& R_line);
	
private:
	std::vector<Object*> objs;
	Graphics& gfx;
	PerspectiveScreenTransformer pst;
	Pixel_Shader* ps;
	Vertex_Shader* vs;
	ZBuffer zbuffer;
};

