#include "stdafx.h"
#include "MaterialLoader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace Basic3D
{
	namespace MaterialLoader
	{
		void LoadMaterial(std::ifstream& inFile, Material& material);

		void LoadMaterial(std::ifstream& inFile, Material& material)
		{
			std::string line;
			std::stringstream ss;
			std::string tempString;

			while (!inFile.eof())
			{
				getline(inFile, line);
				if (line.length() > 2)
				{
					switch (line.at(0))
					{
					case 'K':
						switch (line.at(1))
						{
						case 'a':
							ss.str("");
							ss.clear();
							ss << line;
							ss >> tempString;
							ss >> material.ambient.x;
							ss >> material.ambient.y;
							ss >> material.ambient.z;
							material.ambient.w = 1.0f;
							break;
						case 'd':
							ss.str("");
							ss.clear();
							ss << line;
							ss >> tempString;
							ss >> material.diffuse.x;
							ss >> material.diffuse.y;
							ss >> material.diffuse.z;
							material.diffuse.w = 1.0f;
							break;
						case 's':
							ss.str("");
							ss.clear();
							ss << line;
							ss >> tempString;
							ss >> material.specular.x;
							ss >> material.specular.y;
							ss >> material.specular.z;
							material.specular.w = 1.0f;
							break;
						}
						break;
					}
					switch (line.at(0))
					{
					case 'N':
						switch (line.at(1))
						{
						case 's':
							ss.str("");
							ss.clear();
							ss << line;
							ss >> tempString;
							ss >> material.shininess;
							break;
						}
					}
					switch (line.at(0))
					{
					case 'd':
						ss.str("");
						ss.clear();
						ss << line;
						ss >> tempString;
						ss >> material.alpha;
						break;
					}
				}
			}
		}

		Material MaterialLoader::Load(char* path)
		{
			Material material;
			std::ifstream inFile;

			inFile.open(path);

			if (!inFile.good())
			{
				std::cerr << "Can't open file " << path << std::endl;
				return material;
			}

			std::cout << path << " Loaded" << std::endl;

			LoadMaterial(inFile, material);

			return material;
		}
	}
}