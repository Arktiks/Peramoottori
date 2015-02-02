#include "ObjectLoader.h"


using namespace PORT;

ObjectLoader* ObjectLoader::instance = nullptr;

ObjectLoader* ObjectLoader::getInstance()
{
	if (instance == nullptr)
		instance = new ObjectLoader();
	
	return instance;
}

void ObjectLoader::loadObject(std::string filePath, std::vector<GLfloat> &_vertices, std::vector<GLushort> &_vertexIndices)
{
	glm::vec3 color = { 0, 0, 0 };
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<unsigned int> temp_uvIndices;
	std::string buffer;

	buffer = FileLoader::getInstance()->loadFile(filePath);

	std::stringstream stream(buffer);


	char temp[128];
	while (	stream.getline(temp, sizeof(temp), '\n'))
	{
		char lineHeader[128];
		
		std::stringstream testi(temp);
		
		while (testi.getline(lineHeader, sizeof(lineHeader), ' '))
		{			
			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
#if defined WIN32
				sscanf_s(temp, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
#elif defined ANDROID
				sscanf(temp, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
#endif
				
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				float temp_uv;
#if defined WIN32
				sscanf_s(temp, "vt %f %f %f", &uv.x, &uv.y, &temp_uv);
#elif defined ANDROID
				sscanf(temp, "vt %f %f %f", &uv.x, &uv.y, &temp_uv);
#endif
				temp_uvs.push_back(uv);
			}

			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3];
#if defined WIN32
				int matches = sscanf_s(temp, "f %d/%d %d/%d %d/%d", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
#elif defined ANDROID
				int matches = sscanf(temp, "f %d/%d %d/%d %d/%d", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
#endif
				if (matches != 6)
				{
#if defined WIN32
					printf("Fail känt bii red");
#elif defined ANDROID
					LOG("Fail känt bii red");
#endif
				}

				_vertexIndices.push_back(vertexIndex[0]);
				_vertexIndices.push_back(vertexIndex[1]);
				_vertexIndices.push_back(vertexIndex[2]);

				temp_uvIndices.push_back(uvIndex[0]);
				temp_uvIndices.push_back(uvIndex[1]);
				temp_uvIndices.push_back(uvIndex[2]);
			}
		}
	}

	unsigned vecSize = _vertexIndices.size() * 8;

	_vertices.resize(vecSize);
	for (unsigned int i = 0; i < _vertexIndices.size(); i++)
	{
		_vertexIndices.at(i) -= 1;
		unsigned int vertexIndex = _vertexIndices[i];
		glm::vec3 vertex = temp_vertices[_vertexIndices[i]];
	
		_vertices[i * 8] = vertex.x;
		_vertices[i * 8 + 1] = vertex.y;
		_vertices[i * 8 + 2] = vertex.z;
	
		_vertices[i * 8 + 3] = color.x;
		_vertices[i * 8 + 4] = color.y;
		_vertices[i * 8 + 5] = color.z;
	
		temp_uvIndices.at(i) -= 1;
		unsigned int uvIndex = temp_uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex];
	
		_vertices[i * 8 + 6] = uv.x;
		_vertices[i * 8 + 7] = uv.y;
	}

	for (GLushort i = 0; i < _vertexIndices.size(); i++)
	{
		_vertexIndices[i] = i;
	}
	
}