#pragma once
#include "Model.h"


struct DiceModel
{
	static std::vector<size_t> GetTriIndiciesList()
	{
		return{
				0,2,1,		2,3,1,
				4,8,5,		5,8,9,
				2,6,3,		3,6,7,
				4,5,7,		4,7,6,
				2,10,11,	2,11,6,
				12,3,7,		12,7,13
		};
	}
	static Model MakeDiceModel(float size)
	{
		std::vector<Vertex> tmp_model;
		tmp_model.reserve(14);
		const float side = size / 2.0f;

		const auto ConvertTexCoord = [](float u, float v)
		{
			return Vec2{ (u + 1.0f) / 3.0f,v / 4.0f };
		};
		tmp_model.emplace_back(Vec3{ -side, -side, -side },		ConvertTexCoord(1.0f, 0.0f));	//0
		tmp_model.emplace_back(Vec3{ side, -side, -side },		ConvertTexCoord(0.0f, 0.0f));	//1
		tmp_model.emplace_back(Vec3{ -side, side, -side },		ConvertTexCoord(1.0f, 1.0f));	//2
		tmp_model.emplace_back(Vec3{ side, side, -side },		ConvertTexCoord(0.0f, 1.0f));	//3
		tmp_model.emplace_back(Vec3{ -side, -side, side },		ConvertTexCoord(1.0f, 3.0f));	//4
		tmp_model.emplace_back(Vec3{ side, -side, side },		ConvertTexCoord(0.0f, 3.0f));	//5
		tmp_model.emplace_back(Vec3{ -side, side, side },		ConvertTexCoord(1.0f, 2.0f));	//6
		tmp_model.emplace_back(Vec3{ side, side, side },		ConvertTexCoord(0.0f, 2.0f));	//7
		tmp_model.emplace_back(Vec3{ -side, -side, -side },		ConvertTexCoord(1.0f, 4.0f));	//8
		tmp_model.emplace_back(Vec3{ side, -side, -side },		ConvertTexCoord(0.0f, 4.0f));	//9
		tmp_model.emplace_back(Vec3{ -side, -side, -side },		ConvertTexCoord(2.0f, 1.0f));	//10
		tmp_model.emplace_back(Vec3{ -side, -side, side },		ConvertTexCoord(2.0f, 2.0f));	//11
		tmp_model.emplace_back(Vec3{ side, -side, -side },		ConvertTexCoord(-1.0f, 1.0f));	//12
		tmp_model.emplace_back(Vec3{ side, -side, side },		ConvertTexCoord(-1.0f, 2.0f));	//13


		return { tmp_model, GetTriIndiciesList(), Surface::FromFile(L"Images\\dice_skin.png") };
	}
};