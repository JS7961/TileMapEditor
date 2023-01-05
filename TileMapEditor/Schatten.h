#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <GL/glew.h>


class Schatten
{

public:

	std::string vstext;
	std::string fstext;

	unsigned int shaderid;








	Schatten();

	void Bind();
	void UnBind();

	unsigned int GetShaderid();


   void SchattenEinlesen(std::string DatenPfadShader);


};

