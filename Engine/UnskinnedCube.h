#pragma once
#include "Model.h"

struct UnskinnedCube
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
	static Model MakeUnskinedCube(float size)
	{
		std::vector<Vertex> tmp_model;
		tmp_model.reserve(14);
		const float side = size / 2.0f;

		const auto ConvertTexCoord = [](float u, float v)
		{
			return Vec2{ (u + 1.0f) / 3.0f,v / 4.0f };
		};
		tmp_model.emplace_back(Vec3{ -side, -side, -side });	//0
		tmp_model.emplace_back(Vec3{ side, -side, -side });		//1
		tmp_model.emplace_back(Vec3{ -side, side, -side });		//2
		tmp_model.emplace_back(Vec3{ side, side, -side });		//3
		tmp_model.emplace_back(Vec3{ -side, -side, side });		//4
		tmp_model.emplace_back(Vec3{ side, -side, side });		//5
		tmp_model.emplace_back(Vec3{ -side, side, side });		//6
		tmp_model.emplace_back(Vec3{ side, side, side });		//7
		tmp_model.emplace_back(Vec3{ -side, -side, -side });	//8
		tmp_model.emplace_back(Vec3{ side, -side, -side });		//9
		tmp_model.emplace_back(Vec3{ -side, -side, -side });	//10
		tmp_model.emplace_back(Vec3{ -side, -side, side });		//11
		tmp_model.emplace_back(Vec3{ side, -side, -side });		//12
		tmp_model.emplace_back(Vec3{ side, -side, side });		//13


		return { tmp_model, GetTriIndiciesList()};
	}
};