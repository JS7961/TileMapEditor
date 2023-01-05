#pragma once

#include <GL/glew.h>
#include <vector>

struct vertex
{
	float x , y , z , r, g, b, a,u,v;
};

class VertexBuffer
{

	unsigned int vertexbufferid,vao;

public:
	std::vector<vertex> vertexliste;

public:

	VertexBuffer();
	VertexBuffer(vertex* vertexliste, unsigned int vertexanzahl);

	void VertexBufferErstellen();
	void Bind();
	void UnBind();
	void DeleteBuffer();
	
	~VertexBuffer();


};

