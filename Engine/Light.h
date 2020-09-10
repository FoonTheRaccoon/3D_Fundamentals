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
		// vertex to light data
		const Vec3 v_to_l = pos - vert.worldPos;
		const float dist = v_to_l.Len();
		const Vec3 dir = v_to_l / dist;
		// calculate attenuation
		const float attenuation = 1.0f /
			(constant_attenuation + linear_attenuation * dist * quadradic_attenuation * sq(dist));
		// calculate intensity based on angle of incidence and attenuation
		const float d = diffuse * attenuation;

		float result = (vert.norm.GetNormalized() * dir) * intensity * d;

		result = std::clamp(result, ambient, diffuse);

		return result;
	}
	float SetPixelLightShadingBias(const Triangle& tri)
	{
		// vertex to light data
		const Vec3 v_to_l = pos - tri.triCenter;
		const float dist = v_to_l.Len();
		const Vec3 dir = v_to_l / dist;
		// calculate attenuation
		const float attenuation = 1.0f /
			(constant_attenuation + linear_attenuation * dist * quadradic_attenuation * sq(dist));
		// calculate intensity based on angle of incidence and attenuation
		const float d = diffuse * attenuation;

		float result = (tri.faceNorm * dir) * intensity * d;

		result = std::clamp(result, ambient, diffuse);

		return result;
	}
	const std::vector<Triangle>& GetTriangles() const
	{
		return model.triangles;
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
	float linear_attenuation = 1.0f;
	float quadradic_attenuation = 1.5f;
	float constant_attenuation = 1.0f;
	Vec3 pos = { 0.0f, 0.0f , 1.0f};
	Model model;
};
