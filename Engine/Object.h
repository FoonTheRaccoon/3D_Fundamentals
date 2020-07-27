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
	Object(Keyboard& kbd, Mouse& mouse, std::vector<Vertex> verts, Surface texture = Surface::DefaultSurface())
		: kbd(kbd), mouse(mouse), model(std::move(verts),std::move(texture))
	{}
	void Update(float dt);
	virtual IndexedTriangleList GetTriangles() const = 0;
	const Vec3& GetTheta() const
	{
		return theta;
	}
	const Vec3& GetPos() const
	{
		return pos;
	}
	Surface& GetTexture()
	{
		return model.texture;
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