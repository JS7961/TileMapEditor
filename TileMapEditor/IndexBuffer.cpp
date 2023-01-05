#include "IndexBuffer.h"




IndexBuffer::IndexBuffer(unsigned int* indexliste, unsigned int indexanzahl)
{
	glGenBuffers(1, &indexbufferid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexanzahl, indexliste, GL_STATIC_DRAW);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferid);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{

	glDeleteBuffers(1, &indexbufferid);

}