#pragma once

#include <GL/glew.h>



class IndexBuffer
{

	unsigned int indexbufferid, vao;


public:

	IndexBuffer(unsigned int* indexliste, unsigned int indexanzahl);

	void Bind();
	void UnBind();

	~IndexBuffer();


};

