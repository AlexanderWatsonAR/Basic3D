#include "stdafx.h"
#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace Basic3D
{
	namespace MeshLoader
	{
		namespace
		{
			std::vector<Mesh> meshes;
			ReturnableMesh returnMesh;
		}

		void LoadVertices(std::vector<Vertex>& vertices, std::string& lastLine);
		void LoadTexCoords(std::vector<TexCoord>& texCoords, std::string& line);
		void LoadNormals(std::vector<Vector3>& normals, std::string& lastLine);
		void LoadIndices(std::vector<GLushort>& indicies, std::string& lastLine);
		void ConvertToMesh(Mesh* mesh, std::vector<Vertex>& vertices, std::vector<Vector3>& normals, std::vector<TexCoord>& texCoords, std::vector<GLushort>& indices);

		void LoadVertices(std::vector<Vertex>& vertices, std::string& line)
		{
			std::stringstream ss;
			std::string tempString;

			Vertex v;

			ss.str("");
			ss.clear();
			ss << line;

			ss >> tempString;
			ss >> v.x;
			ss >> v.y;
			ss >> v.z;

			vertices.push_back(v);
		}

		void LoadTexCoords(std::vector<TexCoord>& texCoords, std::string& line)
		{
			std::stringstream ss;
			std::string tempString;

			TexCoord t;
			float tempFloat;

			ss.str("");
			ss.clear();
			ss << line;

			ss >> tempString;
			ss >> t.u;
			ss >> t.v;
			ss >> tempFloat;

			texCoords.push_back(t);
		}

		void LoadNormals(std::vector<Vector3>& normals, std::string& line)
		{
			std::stringstream ss;
			std::string tempString;

			Vector3 n;

			ss.str("");
			ss.clear();
			ss << line;

			ss >> tempString;
			ss >> n.x;
			ss >> n.y;
			ss >> n.z;

			normals.push_back(n);
		}

		void LoadIndices(std::vector<GLushort>& indicies, std::string& line)
		{
			std::stringstream ss;
			std::string tempString;

			std::string faces[3];

			ss.str("");
			ss.clear();
			ss << line;

			ss >> tempString;
			ss >> faces[0];
			ss >> faces[1];
			ss >> faces[2];

			for (int i = 0; i < 3; i++)
			{
				ss.str("");
				ss.clear();
				ss << faces[i];
				getline(ss, line, '/');
				indicies.push_back(stoi(line) - 1);
				getline(ss, line, '/');
				indicies.push_back(stoi(line) - 1);
				getline(ss, line, '/');
				indicies.push_back(stoi(line) - 1);
			}

		}

		void ConvertToMesh(Mesh* mesh, std::vector<Vertex>& vertices, std::vector<Vector3>& normals, std::vector<TexCoord>& texCoords, std::vector<std::vector<GLushort>>& indices)
		{
			int indexCount = 0;

			for (unsigned int i = 0; i < indices.size(); i++)
			{
				std::vector<GLushort> currentIndices;
				for (unsigned int c = 0; c < indices[i].size(); c += 3)
				{
					currentIndices.push_back(indexCount);

					mesh->vertices.push_back(vertices[indices[i][c]]);
					mesh->texCoords.push_back(texCoords[indices[i][c + 1]]);
					mesh->normals.push_back(normals[indices[i][c + 2]]);

					indexCount++;
				}
				mesh->indices.push_back(currentIndices);
			}
		}

		GLuint MeshLoader::Load(const char* path)
		{
			std::vector<Vertex> Vertices;
			std::vector<Vector3> Normals;
			std::vector<TexCoord> texCoords;
			std::vector<std::vector<GLushort>> currentIndices;

			std::string line;
			std::stringstream ss;
			std::string tempString;

			Mesh mesh;

			std::ifstream inFile;

			inFile.open(path);

			if (!inFile.good())
			{
#if _DEBUG
				std::cerr << "Can't open file " << path << std::endl;
#endif
				return -1;
			}

			while (!inFile.eof())
			{
				getline(inFile, line);

				if (line.length() > 2)
				{
					switch (line.at(0))
					{
					case 'v':
						switch (line.at(1))
						{
						case ' ':
							LoadVertices(Vertices, line);
							break;
						case 'n':
							LoadNormals(Normals, line);
							break;
						case 't':
							LoadTexCoords(texCoords, line);
							break;
						}
						break;
					case 'f':
						LoadIndices(currentIndices.back(), line);
						break;
					case '#':
						ss.str("");
						ss.clear();
						ss << line;

						ss >> tempString;
						ss >> tempString;

						if (tempString == "object")
						{
							ss >> tempString;

							mesh.meshNames.push_back(tempString);

							std::vector<GLushort> indices;
							currentIndices.push_back(indices);
						}
						break;
					}
				}
			}
#if _DEBUG
			std::cout << path << " Loaded" << std::endl;
#endif

			ConvertToMesh(&mesh, Vertices, Normals, texCoords, currentIndices);

			meshes.push_back(mesh);

			const GLuint meshID = meshes.size() - 1;

			return meshID;
		}

		Mesh * MeshLoader::GetMesh(GLuint meshID)
		{
			if(!meshes.empty() && meshID < meshes.size())
				return &meshes.at(meshID);
			return nullptr;
		}

		ReturnableMesh MeshLoader::GetReturnableMesh(GLuint meshID)
		{
			returnMesh.indices = &meshes[meshID].indices[0][0];
			returnMesh.meshNames = &meshes[meshID].meshNames[0];
			returnMesh.normals = &meshes[meshID].normals[0];
			returnMesh.texCoords = &meshes[meshID].texCoords[0];
			returnMesh.vertices = &meshes[meshID].vertices[0];
			return returnMesh;
		}
	}
}