#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex
{
	float position[3];
	float texCoord[2];
	float normal[3];
};

class OBJLoader
{
public:
	OBJLoader() { }

	bool Load(const std::string& path)
	{
		std::ifstream file(path);

		if (!file.is_open())
			return false;

		std::string line;

		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string prefix;
			iss >> prefix;

			if (prefix == "v") 
			{
				float x, y, z;
				iss >> x >> y >> z;
				positions.insert(positions.end(), { x, y, z });
			}
			else if (prefix == "vt") 
			{
				float u, v;
				iss >> u >> v;
				textureCoords.insert(textureCoords.end(), { u, v });
			}
			else if (prefix == "vn") 
			{
				float x, y, z;
				iss >> x >> y >> z;
				normals.insert(normals.end(), { x, y, z });
			}
			else if (prefix == "f") 
			{
				ParseFace(line.substr(2));
			}
		}

		return true;
	}

	int ToBuffer()
	{
		unsigned int VAO, VBO;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		return VAO;
	}

private:
	std::vector<float> positions;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<Vertex> vertices;

	void ParseFace(const std::string& faceData) 
	{
		std::istringstream iss(faceData);
		std::string vertexStr;
		std::vector<Vertex> faceVertices;

		while (iss >> vertexStr) 
		{
			Vertex vertex = ParseVertex(vertexStr);
			faceVertices.push_back(vertex);
		}

		if (faceVertices.size() == 4) 
		{
			vertices.insert(vertices.end(), 
			{
				faceVertices[0], faceVertices[1], faceVertices[2],
				faceVertices[0], faceVertices[2], faceVertices[3]
			});
		}
		else if (faceVertices.size() == 3) 
		{
			vertices.insert(vertices.end(), faceVertices.begin(), faceVertices.end());
		}
	}

	Vertex ParseVertex(const std::string& vertexStr)
	{
		Vertex vertex = {};

		size_t pos1 = vertexStr.find('/');
		size_t pos2 = vertexStr.find('/', pos1 + 1);

		int vIdx = std::stoi(vertexStr.substr(0, pos1)) - 1;
		int vtIdx = -1, vnIdx = -1;

		if (pos1 != std::string::npos && pos2 != std::string::npos) 
		{
			if (pos2 > pos1 + 1) 
				vtIdx = std::stoi(vertexStr.substr(pos1 + 1, pos2 - pos1 - 1)) - 1;

			vnIdx = std::stoi(vertexStr.substr(pos2 + 1)) - 1;
		}

		if (vIdx >= 0 && vIdx * 3 + 2 < positions.size()) 
		{
			vertex.position[0] = positions[vIdx * 3];
			vertex.position[1] = positions[vIdx * 3 + 1];
			vertex.position[2] = positions[vIdx * 3 + 2];
		}

		if (vtIdx >= 0 && vtIdx * 2 + 1 < textureCoords.size()) 
		{
			vertex.texCoord[0] = textureCoords[vtIdx * 2];
			vertex.texCoord[1] = textureCoords[vtIdx * 2 + 1];
		}

		if (vnIdx >= 0 && vnIdx * 3 + 2 < normals.size()) 
		{
			vertex.normal[0] = normals[vnIdx * 3];
			vertex.normal[1] = normals[vnIdx * 3 + 1];
			vertex.normal[2] = normals[vnIdx * 3 + 2];
		}

		return vertex;
	}

};

#endif 