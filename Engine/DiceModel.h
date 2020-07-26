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
	static TexVertex MakeDiceModel(float size)
	{
		TexVertex tmp_model;
		tmp_model.pos.reserve(14);
		tmp_model.texCor.reserve(14);
		const float side = size / 2.0f;
		tmp_model.pos.emplace_back(-side, side, -side);		//1
		tmp_model.texCor.emplace_back(0.0f, 0.333f);
		tmp_model.pos.emplace_back(-side, side, side);		//2
		tmp_model.texCor.emplace_back(0.0f, 0.666f);
		tmp_model.pos.emplace_back(-side, side, -side);		//3
		tmp_model.texCor.emplace_back(0.25f, 0.0f);
		tmp_model.pos.emplace_back(-side, -side, -side);	//4
		tmp_model.texCor.emplace_back(0.25f, 0.333f);
		tmp_model.pos.emplace_back(-side, -side, side);		//5
		tmp_model.texCor.emplace_back(0.25f, 0.666f);
		tmp_model.pos.emplace_back(-side, side, side);		//6
		tmp_model.texCor.emplace_back(0.25f, 1.0f);
		tmp_model.pos.emplace_back(side, side, -side);		//7
		tmp_model.texCor.emplace_back(0.5f, 0.0f);
		tmp_model.pos.emplace_back(side, -side, -side);		//8
		tmp_model.texCor.emplace_back(0.5f, 0.333f);
		tmp_model.pos.emplace_back(side, -side, side);		//9
		tmp_model.texCor.emplace_back(0.5f, 0.666f);
		tmp_model.pos.emplace_back(side, side, side);		//10
		tmp_model.texCor.emplace_back(0.5f, 1.0f);
		tmp_model.pos.emplace_back(side, side, -side);		//11
		tmp_model.texCor.emplace_back(0.75f, 0.333f);
		tmp_model.pos.emplace_back(side, side, side);		//12
		tmp_model.texCor.emplace_back(0.75f, 0.666f);
		tmp_model.pos.emplace_back(-side, side, -side);		//13
		tmp_model.texCor.emplace_back(1.0f, 0.333f);
		tmp_model.pos.emplace_back(-side, side, side);		//14
		tmp_model.texCor.emplace_back(1.0f, 0.666f);
		return { tmp_model };
	}

};