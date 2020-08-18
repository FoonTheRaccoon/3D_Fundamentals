#pragma once
#include "Mat3.h"
#include "Vec3.h"
#include "Triangle.h"
#include "MainWindow.h"
#include "ObjLoader.h"

class Light 
{
public:
	Light(Model model = ObjLoader::MakeModelFromObjFile(L"Models\\sphere.obj"))
		: model(std::move(model))
	{}
	void Update(MainWindow& wnd, float dt)
	{
		if (wnd.kbd.KeyIsPressed('L'))
		{
			pos.x = pos.x + speed * dt;
		}
		if (wnd.kbd.KeyIsPressed('I'))
		{
			pos.y = pos.y + speed * dt;
		}
		if (wnd.kbd.KeyIsPressed('U'))
		{
			pos.z = pos.z + speed * dt;
		}
		if (wnd.kbd.KeyIsPressed('J'))
		{
			pos.x = pos.x - speed * dt;
		}
		if (wnd.kbd.KeyIsPressed('K'))
		{
			pos.y = pos.y - speed * dt;
		}
		if (wnd.kbd.KeyIsPressed('O'))
		{
			pos.z = pos.z - speed * dt;
		}
	}
	float SetPixelLightShadingBias(const Vertex& vert)
	{
		const Vec3 lightNorm = pos.MakeNormVecFromPos(vert.pos);

		float result = ((-vert.norm.GetNormalized()) * lightNorm) * intensity;

		result = std::clamp(result, ambient, diffuse);

		return result;
	}
	float SetPixelLightShadingBias(const Triangle& tri)
	{
		const Vec3 faceAvg = (tri.v0.pos + tri.v1.pos + tri.v0.pos) / 3.0f;
		const Vec3 lightNorm = pos.MakeNormVecFromPos(faceAvg);


		float result = ((-tri.faceNorm) * lightNorm) * intensity;

		result = std::clamp(result, ambient, diffuse);

		return result;
	}
	const std::vector<Triangle>& GetTriangles() const
	{
		return model.triangles;
	}
	const Vec3& GetTheta() const
	{
		return theta;
	}
	const Vec3& GetPos() const
	{
		return pos;
	}
	Surface* GetTexturePtr()
	{
		return &model.texture;
	}
private:
	float intensity = 1.0f;
	float ambient = 0.05f;
	float diffuse = 0.9f;
	float speed = 1.0f;
	Vec3 pos = { 0.0f, 0.0f , 1.0f};
	Vec3 theta = { 0.0f ,0.0f ,0.0f };
	Model model;
};
