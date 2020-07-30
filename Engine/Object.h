#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "PerspectiveScreenTransformer.h"
#include "IndexedLineList.h"
#include "IndexedTriangleList.h"
#include "Model.h"

class Object
{
public:
	Object(Keyboard& kbd, Mouse& mouse, Model model)
		: kbd(kbd), mouse(mouse), model(std::move(model))
	{}
	void Update(float dt);
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
protected:
	static constexpr float dTheta = PI;
	Vec3 pos = { 0.0f ,0.0f ,2.0f };
	Vec3 theta = { 0.0f ,0.0f ,0.0f };
	Model model;
	//Refs
	Keyboard& kbd;
	Mouse& mouse;
};