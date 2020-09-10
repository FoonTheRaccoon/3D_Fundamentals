#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Model.h"

struct ObjLoader
{
	//Main Loading function
	static Model MakeModelFromObjFile(const std::wstring& file_in)
	{
		std::ifstream file(file_in);

		if (file)
		{
			//File reading variables
			char line[512];

			std::string lineBuffer;
			std::string firstWord;

			//Model making variables
			std::vector<Vec3> verticies;
			std::vector<Vec2> texCor;
			std::vector<Vec3> verticiesNorm;
			std::vector<Triangle> triangles;


			while (file.getline(line, 512))
			{
				lineBuffer = line;

				firstWord = GetFirstWordInLine(lineBuffer);

				if (firstWord == "v") //Vertice line
				{
					PullVerticeFromLine(lineBuffer, verticies);
				}
				else if (firstWord == "vt") //Tecture coordinate line
				{
					PullTextureCoordFromLine(lineBuffer, texCor);
				}
				else if (firstWord == "vn") //Verticie normal line
				{
					PullVerticeNormFromLine(lineBuffer, verticiesNorm);
				}
				else if (firstWord == "f") //Face line (Triangles only for now)
				{
					MakePolyFromLine(lineBuffer, verticies, texCor, verticiesNorm, triangles);
				}
			}

			return { triangles };
		}
		return MakeModelFromObjFile(L"Models\\sphere.obj");
	}
private:
	//Helper functions
	static std::string GetFirstWordInLine(const std::string& line)
	{
		std::string resultBuffer;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				resultBuffer += line[i];
			}
			else
			{
				return resultBuffer;
			}
		}

		return resultBuffer;
	}
	//Extract verticies from a line
	static void PullVerticeFromLine(const std::string& line, std::vector<Vec3>& verticies)
	{
		std::string numBuf;

		float vec[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		int index = 0;

		for (int i = 2; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				numBuf += line[i];
			}
			else
			{
				vec[index] = std::stof(numBuf);
				numBuf.clear();
				++index;
			}
		}
		//For last element
		vec[index] = std::stof(numBuf);

		verticies.emplace_back(Vec3{ vec[0], vec[1], vec[2] });
	}
	//Extract texture coordinates from a line
	static void PullTextureCoordFromLine(const std::string& line, std::vector<Vec2>& texCor)
	{
		std::string numBuf;

		float vec[3] = { 0.0f, 0.0f, 0.0f};

		int index = 0;

		for (int i = 3; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				numBuf += line[i];
			}
			else
			{
				vec[index] = std::stof(numBuf);
				numBuf.clear();
				++index;
			}
		}
		
		//For last element
		vec[index] = std::stof(numBuf);

		texCor.emplace_back(Vec2{ vec[0], vec[1]});
	}
	//Extract the vertice normal from a line
	static void PullVerticeNormFromLine(const std::string& line, std::vector<Vec3>& verticiesNorm)
	{
		std::string numBuf;

		float vec[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		int index = 0;

		for (int i = 3; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				numBuf += line[i];
			}
			else
			{
				vec[index] = std::stof(numBuf);
				numBuf.clear();
				++index;
			}
		}
		
		//For last element
		vec[index] = std::stof(numBuf);

		verticiesNorm.emplace_back(Vec3{ vec[0], vec[1], vec[2] });
	}
	//Take all data and make a triangle(only for now) from a data line.
	static void MakePolyFromLine(const std::string& line, const std::vector<Vec3>& verticies, const std::vector<Vec2>& texCor, const std::vector<Vec3>& verticiesNorm, std::vector<Triangle>& triangles)
	{
		std::string numBuf;

		Vec3 verts[3];
		Vec2 texCors[3];
		Vec3 vertNorm[3];

		int slashIndex = 0;
		int spaceIndex = 0;

		for (int i = 2; i < line.size(); ++i)
		{
			if (line[i] != ' ')
			{
				if (line[i] == '/')
				{
					int index = std::stoi(numBuf) - 1;
					if (slashIndex == 0)
					{
						verts[spaceIndex] = verticies[index];
					}
					else if (slashIndex == 1)
					{
						texCors[spaceIndex] = texCor[index];
					}
					++slashIndex;
					numBuf.clear();
				}
				else
				{
					numBuf += line[i];
				}
			}
			else
			{
				int index = std::stoi(numBuf) - 1;
				vertNorm[spaceIndex] = verticiesNorm[index];
				numBuf.clear();
				++spaceIndex;
				slashIndex = 0;
			}
		}
		int index = std::stoi(numBuf) - 1;
		vertNorm[spaceIndex] = verticiesNorm[index];

		Vertex v0 = { verts[0], texCors[0], vertNorm[0] };
		Vertex v1 = { verts[1], texCors[1], vertNorm[1] };
		Vertex v2 = { verts[2], texCors[2], vertNorm[2] };

		triangles.emplace_back(v0, v1, v2, Colors::MakeRGB(rand() % 255, rand() % 255, rand() % 255));
	}
};