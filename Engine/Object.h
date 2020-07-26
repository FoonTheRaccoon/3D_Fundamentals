#pragma once
#include "TexVertex.h"
#include "MainWindow.h"
#include "Graphics.h"
#include "PubeScreenTransformer.h"
#include "IndexedLineList.h"
#include "IndexedTriangleList.h"

class Object
{
public:
	Object(Keyboard& kbd, Mouse& mouse, TexVertex model, Surface& texture = Surface::DefaultSurface())
		: kbd(kbd), mouse(mouse), model(std::move(model)), texture(texture)
	{}
	void Update(float dt);
	void DrawTextureless(Graphics& gfx, PubeScreenTransformer& pst);
	void DrawTextured(Graphics& gfx, PubeScreenTransformer& pst);
protected:
	void TransformVerts(IndexedTriangleList& triangles);
	void SetCullFlags(IndexedTriangleList& triangles);
	virtual IndexedTriangleList GetTriangles() const = 0;
protected:
	static constexpr float dTheta = PI;
	float offset_z = 2.0f;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
	TexVertex model;
	//Refs
	Surface& texture;
	Keyboard& kbd;
	Mouse& mouse;
	//Color Wheel
protected:
	const Color colors[12] = {
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray,
		Colors::Green,
		Colors::LightGray,
		Colors::Magenta,
		Colors::Red,
		Colors::White,
		Colors::Yellow,
		Colors::MakeRGB(100u, 0u,100u),
		Colors::MakeRGB(200u,200u, 0u),
		Colors::MakeRGB(100u,200u, 255u)
	};
};