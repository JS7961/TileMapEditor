#include "Schatten.h"




Schatten::Schatten()
{
}

void Schatten::Bind()
{
	glUseProgram(shaderid);
}

void Schatten::UnBind()
{
	glUseProgram(0);
}

unsigned int Schatten::GetShaderid()
{
	return shaderid;
}

void Schatten::SchattenEinlesen(std::string DatenPfadShader)
{
	std::ifstream in;
	// Open the file

	std::string p1, p2;

	p1 = DatenPfadShader + "basic.vs";
	p2 = DatenPfadShader + "basic.fs";

	//in.open("D:\\VisualStudioProjekte\\TileMapEditor\\basic.vs");

	in.open(p1);

	if (in.fail())
	{
		std::cout << "fail !!!???";
	}

	std::string line="", gesamt = "";

	while (true)
	{
		gesamt += line;
		gesamt += "\n";
		getline(in, line);
		if (in.fail())
		{
			break;
		}
	}

	vstext = gesamt;

	//std::cout << vstext;

	gesamt = "";

	in.close();

	//in.open("D:\\VisualStudioProjekte\\TileMapEditor\\basic.fs");

	in.open(p2);

	if (in.fail())
	{
		std::cout << "fail !!!???";
	}

	line = "";

	while (true)
	{
		gesamt += line;
		gesamt += "\n";
		getline(in, line);
		if (in.fail())
		{
			break;
		}
	}

	fstext = gesamt;

	//std::cout << fstext;

	unsigned int programm = glCreateProgram();
	unsigned int vs;
	unsigned int fs;


	unsigned int id,id2;

	id = glCreateShader(GL_VERTEX_SHADER);
	const char* chartext = vstext.c_str();
	glShaderSource(id, 1, &chartext, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "\n Error:   " << message;
	}

	vs = id;

	id2 = glCreateShader(GL_FRAGMENT_SHADER);
	const char* chartext2 = fstext.c_str();
	glShaderSource(id2, 1, &chartext2, 0);
	glCompileShader(id2);

	fs = id2;


	glAttachShader(programm, vs);
	glAttachShader(programm, fs);

	glLinkProgram(programm);

	shaderid = programm;
}


