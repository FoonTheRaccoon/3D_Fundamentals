#pragma once
#include "Object.h"


class DiceModel : public Object
{
public:
	DiceModel(Keyboard& kbd, Mouse& mouse, float size)
		: Object(kbd, mouse, MakeDiceModel(size), Surface::FromFile(L"Images\\dice_unwrap.png"))
	{}
	IndexedTriangleList GetTriangles() const override
	{
		return{
			model, {
			0,3,4,		0,1,4,
			2,3,7,		2,6,8,
			3,7,8,		3,4,8,
			4,5,9,		4,8,9,
			7,8,11,		7,10,11,
			10,11,13,	10,12,13
			}
		};
	}
	static std::vector<TexVertex> MakeDiceModel(float size)
	{
		std::vector<TexVertex> tmp_model;
		tmp_model.reserve(14);
		const float side = size / 2.0f;
		tmp_model.emplace_back(Vec3{ -side, side, -side },	Vec2{ 0.0f, 0.333f});	//1
		tmp_model.emplace_back(Vec3{ -side, side, side },	Vec2{ 0.0f, 0.666f });	//2
		tmp_model.emplace_back(Vec3{ -side, side, -side },	Vec2{ 0.25f, 0.0f });	//3
		tmp_model.emplace_back(Vec3{ -side, -side, -side },	Vec2{ 0.25f, 0.333f });	//4
		tmp_model.emplace_back(Vec3{ -side, -side, side },	Vec2{ 0.25f, 0.666f });	//5
		tmp_model.emplace_back(Vec3{ -side, side, side },	Vec2{ 0.25f, 1.0f });	//6
		tmp_model.emplace_back(Vec3{ side, side, -side },	Vec2{ 0.5f, 0.0f });	//7
		tmp_model.emplace_back(Vec3{ side, -side, -side },	Vec2{ 0.5f, 0.333f });	//8
		tmp_model.emplace_back(Vec3{ side, -side, side },	Vec2{ 0.5f, 0.666f });	//9
		tmp_model.emplace_back(Vec3{ side, side, side },	Vec2{ 0.5f, 1.0f });	//10
		tmp_model.emplace_back(Vec3{ side, side, -side },	Vec2{ 0.75f, 0.333f });	//11
		tmp_model.emplace_back(Vec3{ side, side, side },	Vec2{ 0.75f, 0.666f });	//12
		tmp_model.emplace_back(Vec3{ -side, side, -side },	Vec2{ 1.0f, 0.333f });	//13
		tmp_model.emplace_back(Vec3{ -side, side, side },	Vec2{ 1.0f, 0.666f });	//14
		return tmp_model;
	}

};