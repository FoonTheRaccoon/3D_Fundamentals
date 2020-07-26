#pragma once
#include "Object.h"


class UnskinnedCube : public Object
{
public:
	UnskinnedCube(Keyboard& kbd, Mouse& mouse, float size )
		: Object(kbd, mouse, MakeUnskinedCube(size))
	{}
	
	IndexedTriangleList GetTriangles() const override
	{
		return{
			model, {
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
			}
		};
	}
	static std::vector<TexVertex> MakeUnskinedCube(float size)
	{
		std::vector<TexVertex> tmp_model;
		tmp_model.reserve(8);
		const float side = size / 2.0f;
		tmp_model.emplace_back(Vec3{ -side, -side, -side });
		tmp_model.emplace_back(Vec3{ side, -side, -side });
		tmp_model.emplace_back(Vec3{ -side, side, -side });
		tmp_model.emplace_back(Vec3{ side, side, -side });
		tmp_model.emplace_back(Vec3{ -side, -side, side });
		tmp_model.emplace_back(Vec3{ side, -side, side });
		tmp_model.emplace_back(Vec3{ -side, side, side });
		tmp_model.emplace_back(Vec3{ side, side, side });

		return tmp_model;
	}

};