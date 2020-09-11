#pragma once
#include "Mat.h"
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
	float SetPixelLightShadingBias(const Vertex& vert) //Smooth Shading
	{
		const Vec3 surf_norm = vert.norm.GetNormalized();

		// vertex to light data
		const Vec3 v_to_l = pos - vert.worldPos;
		const float dist = v_to_l.Len();
		const Vec3 dir = v_to_l / dist;

		// calculate attenuation
		const float attenuation = 1.0f /
			(constant_attenuation + linear_attenuation * dist + quadradic_attenuation * sq(dist));

		const float result = (surf_norm * dir) * intensity * attenuation;

		const Vec3 w = surf_norm * (v_to_l * surf_norm);
		const Vec3 r = w * 2.0f - v_to_l;
		// calculate specular intensity based on angle between viewing vector and reflection vector, narrow with power function
		const float s = specular_intensity * std::pow(std::max(0.0f, -r.GetNormalized() * vert.worldPos.GetNormalized()), specular_power);

		return std::clamp(result + s, ambient, diffuse);
	}
	float SetPixelLightShadingBias(const Triangle& tri) //Flat Shading
	{
		// vertex to light data
		const Vec3 v_to_l = pos - tri.triCenter;
		const float dist = v_to_l.Len();
		const Vec3 dir = v_to_l / dist;

		// calculate attenuation
		const float attenuation = 1.0f /
			(constant_attenuation + linear_attenuation * dist + quadradic_attenuation * sq(dist));

		const float result = (tri.faceNorm * dir) * intensity * attenuation;

		return std::clamp(result, ambient, diffuse);
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
	float intensity = 2.0f;
	float ambient = 0.01f;
	float diffuse = 0.95f;
	float speed = 1.0f;
	//Diffuse
	float linear_attenuation = 1.0f;
	float quadradic_attenuation = 2.5f;
	float constant_attenuation = 0.3f;
	//Specular
	float specular_power = 60.0f;
	float specular_intensity = 0.6f;

	Vec3 pos = { 0.0f, 0.0f , 1.0f};
	Model model;
};
