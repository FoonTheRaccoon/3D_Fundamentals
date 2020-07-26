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
			model,{
				0,2,1,		2,3,1,
				4,8,5,		5,8,9,
				2,6,3,		3,6,7,
				4,5,7,		4,7,6,
				2,10,11,	2,11,6,
				12,3,7,		12,7,13
			}
		};
	}
	//static std::vector<TexVertex> MakeDiceModel(float size)
	//{
	//	std::vector<TexVertex> tmp_model;
	//	tmp_model.reserve(14);
	//	const float side = size / 2.0f;
	//	tmp_model.emplace_back(Vec3{ -side, side, -side },	Vec2{ 0.0f, 0.333f});	//1
	//	tmp_model.emplace_back(Vec3{ -side, side, side },	Vec2{ 0.0f, 0.666f });	//2
	//	tmp_model.emplace_back(Vec3{ -side, side, -side },	Vec2{ 0.25f, 0.0f });	//3
	//	tmp_model.emplace_back(Vec3{ -side, -side, -side },	Vec2{ 0.25f, 0.333f });	//4
	//	tmp_model.emplace_back(Vec3{ -side, -side, side },	Vec2{ 0.25f, 0.666f });	//5
	//	tmp_model.emplace_back(Vec3{ -side, side, side },	Vec2{ 0.25f, 1.0f });	//6
	//	tmp_model.emplace_back(Vec3{ side, side, -side },	Vec2{ 0.5f, 0.0f });	//7
	//	tmp_model.emplace_back(Vec3{ side, -side, -side },	Vec2{ 0.5f, 0.333f });	//8
	//	tmp_model.emplace_back(Vec3{ side, -side, side },	Vec2{ 0.5f, 0.666f });	//9
	//	tmp_model.emplace_back(Vec3{ side, side, side },	Vec2{ 0.5f, 1.0f });	//10
	//	tmp_model.emplace_back(Vec3{ side, side, -side },	Vec2{ 0.75f, 0.333f });	//11
	//	tmp_model.emplace_back(Vec3{ side, side, side },	Vec2{ 0.75f, 0.666f });	//12
	//	tmp_model.emplace_back(Vec3{ -side, side, -side },	Vec2{ 1.0f, 0.333f });	//13
	//	tmp_model.emplace_back(Vec3{ -side, side, side },	Vec2{ 1.0f, 0.666f });	//14
	//	return tmp_model;
	//}
	static std::vector<TexVertex> MakeDiceModel(float size)
	{
		std::vector<TexVertex> tmp_model;
		tmp_model.reserve(14);
		const float side = size / 2.0f;

		const auto ConvertTexCoord = [](float u, float v)
		{
			return Vec2{ (u + 1.0f) / 3.0f,v / 4.0f };
		};
		tmp_model.emplace_back(Vec3{ -side, -side, -side }, ConvertTexCoord(1.0f, 0.0f)); //0
		tmp_model.emplace_back(Vec3{ side, -side, -side },	ConvertTexCoord(0.0f, 0.0f)); //1
		tmp_model.emplace_back(Vec3{ -side, side, -side },	ConvertTexCoord(1.0f, 1.0f)); //2
		tmp_model.emplace_back(Vec3{ side, side, -side },	ConvertTexCoord(0.0f, 1.0f)); //3
		tmp_model.emplace_back(Vec3{ -side, -side, side },	ConvertTexCoord(1.0f, 3.0f)); //4
		tmp_model.emplace_back(Vec3{ side, -side, side },	ConvertTexCoord(0.0f, 3.0f)); //5
		tmp_model.emplace_back(Vec3{ -side, side, side },	ConvertTexCoord(1.0f, 2.0f)); //6
		tmp_model.emplace_back(Vec3{ side, side, side },	ConvertTexCoord(0.0f, 2.0f)); //7
		tmp_model.emplace_back(Vec3{ -side, -side, -side },	ConvertTexCoord(1.0f, 4.0f)); //8
		tmp_model.emplace_back(Vec3{ side, -side, -side },	ConvertTexCoord(0.0f, 4.0f)); //9
		tmp_model.emplace_back(Vec3{ -side, -side, -side },	ConvertTexCoord(2.0f, 1.0f)); //10
		tmp_model.emplace_back(Vec3{ -side, -side, side },	ConvertTexCoord(2.0f, 2.0f)); //11
		tmp_model.emplace_back(Vec3{ side, -side, -side },	ConvertTexCoord(-1.0f, 1.0f)); //12
		tmp_model.emplace_back(Vec3{ side, -side, side },	ConvertTexCoord(-1.0f, 2.0f)); //13

		return tmp_model;
	}
};