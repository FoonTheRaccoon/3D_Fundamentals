/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	renderer(gfx),
	monkey(ObjLoader::MakeModelFromObjFile(L"Models\\monkey.obj"))
{
	renderer.AddObject(&monkey);
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	dt = ft.Mark();

	monkey.Update(wnd, dt);

	worldLight.Update(wnd, dt);
	
	if (wnd.kbd.KeyIsPressed(VK_LEFT) && !wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		--psList;
		if (psList < 0)
		{
			psList = PixelShader::PtrList.size() - 1;
		}
		renderer.SetPixelShader(PixelShader::PtrList[psList]);
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && !wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		++psList;
		if (psList >= PixelShader::PtrList.size())
		{
			psList = 0;
		}
		renderer.SetPixelShader(PixelShader::PtrList[psList]);
	}
	
	if (wnd.kbd.KeyIsPressed(VK_SHIFT) && wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		--vsList;
		if (vsList < 0)
		{
			vsList = VertexShader::PtrList.size() - 1;
		}
		renderer.SetVertexShader(VertexShader::PtrList[vsList]);
	}
	else if (wnd.kbd.KeyIsPressed(VK_SHIFT) && wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		++vsList;
		if (vsList >= VertexShader::PtrList.size())
		{
			vsList = 0;
		}
		renderer.SetVertexShader(VertexShader::PtrList[vsList]);
	}

	if (wnd.kbd.KeyIsPressed('M'))
	{
		renderer.DropObject(&monkey);
	}

	if (wnd.kbd.KeyIsPressed('Z'))
	{
		renderer.FlipLightMode();
	}
}

void Game::ComposeFrame()
{	
	renderer.Update(dt);
}