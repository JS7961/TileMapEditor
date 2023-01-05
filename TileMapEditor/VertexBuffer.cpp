#include "VertexBuffer.h"

/*

VertexBuffer::VertexBuffer(void* vertexliste, unsigned int vertexanzahl)
{
		
	glGenBuffers(1, &vertexbufferid);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertexanzahl, vertexliste, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), (void*) 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(vertex), (void*) 12 );

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (void*)28);


}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferid);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(vertex), (void*) 12 );

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (void*)28);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
}

VertexBuffer::~VertexBuffer()
{

	glDeleteBuffers(1, &vertexbufferid);

}

*/


//vao variante

VertexBuffer::VertexBuffer()
{
	
}

VertexBuffer::VertexBuffer(vertex* vertexliste, unsigned int vertexanzahl)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexbufferid);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertexanzahl, vertexliste, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), (void*) 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(vertex), (void*) 12 );

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (void*)28);

	glBindVertexArray(0);
}

void VertexBuffer::VertexBufferErstellen()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexbufferid);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertexliste.size(), &vertexliste[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(vertex), (void*)12);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (void*)28);

	glBindVertexArray(0);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferid);
}

void VertexBuffer::UnBind()
{
	glBindVertexArray(0);
}

void VertexBuffer::DeleteBuffer()
{
	vertexliste.clear();
	glDeleteBuffers(1, &vertexbufferid);
}

VertexBuffer::~VertexBuffer()
{
	//vertexliste.clear();
	//glDeleteBuffers(1, &vertexbufferid);
	
}


