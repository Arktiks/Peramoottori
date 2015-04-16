#pragma once
#include <GLES2\gl2.h>


enum bufferType
{
	VERTEX,
	INDEX
};
class Buffer
{

public:
	Buffer();
	void createBuffer(bufferType type);
	void BindBufferData(unsigned size, void *data);
	void BindBufferData();
	bufferType getType(){ return type; };
	GLuint getIndex(){return index; };
	~Buffer();
private:
	void BindVertexNullptr();
	void BindIndexNullptr();
	void BindVertexData(unsigned size, void *data);
	void BindIndexData(unsigned size, void *data);
	GLuint index;
	bufferType type;

};

