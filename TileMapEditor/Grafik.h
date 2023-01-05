#pragma once

#include <iostream>

#include "windows.h"
#include <array>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif


//#include "stb_image.h"

#include "VertexBuffer.h"
#include "Schatten.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

#define SDL_MAIN_HANDLED

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL.h>

#include "glm.hpp"
#include "ext/matrix_transform.hpp"
#include "gtc/matrix_transform.hpp"
#include <vector>


#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")



	inline std::string DatenPfad;



class Kamera
{

public:

	glm::vec3 position;
	glm::mat4 projektion;
	glm::mat4 view;
	glm::mat4 projektionview;

	Kamera(float fov, float breite, float hoehe)
	{
		//glm::mat4 projektionortho = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -10.0f, 100.0f);
		//glm::mat4 projektionperspektive = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

		projektion = glm::perspective(fov / 2, breite / hoehe, 0.1f, 1000.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		position = glm::vec3(0.0f);
	}

	glm::mat4 GetProjektionview()
	{
		return projektionview;
	}

	void KameraUpdate()
	{
		projektionview = projektion * view;
	}

	void KameraBewegen(glm::vec3 v)
	{
		position += v;
		view = glm::translate(view, v * -1.0f);
	}



};

class FpsKamera
{

public:

	glm::vec3 position;
	glm::mat4 projektion;
	glm::mat4 view;
	glm::mat4 projektionview;
	glm::vec3 lookat;
	glm::vec3 up;
	float xrot, yrot;  // pitch, yaw

	FpsKamera(float fov, float breite, float hoehe)
	{
		projektion = glm::perspective(fov / 2, breite / hoehe, 0.1f, 1000.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		position = glm::vec3(0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		yrot = -90.0f;
		xrot = 0.0f;
		MausBewegung(0.0f, 0.0f);
		KameraUpdate();
	}

	glm::mat4 GetProjektionview()
	{
		return projektionview;
	}

	void KameraUpdate()
	{
		view = glm::lookAt(position, position + lookat, up);

		projektionview = projektion * view;
	}

	void KameraBewegen(glm::vec3 v)
	{
		position += v;
		view = glm::translate(view, v * -1.0f);
	}

	void MausBewegung(float xrel, float yrel)
	{
		yrot += xrel;
		xrot -= yrel;
		if (xrot > 89)
		{
			xrot = 89;
		}
		if (xrot < -89)
		{
			xrot = -89;
		}

		glm::vec3 front;
		front.x = cos(glm::radians(xrot)) * cos(glm::radians(yrot));
		front.y = sin(glm::radians(xrot));
		front.z = cos(glm::radians(xrot)) * sin(glm::radians(yrot));

		lookat = glm::normalize(front);
		KameraUpdate();
	}

	void FrontBewegung(float amount)
	{
		KameraBewegen(lookat * amount);
		KameraUpdate();
	}

	void SeitenBewegung(float amount)
	{
		KameraBewegen(glm::normalize(glm::cross(lookat, up)) * amount);
		KameraUpdate();
	}

	void YBewegung(float amount)
	{
		glm::vec3 v = glm::vec3(0, amount, 0);
		KameraBewegen(v);
		KameraUpdate();
	}



};



class Grafik
{
public:
	Schatten Schatten1;

	VertexBuffer MenueElementeBuffer;

	VertexBuffer VorschauBuffer;

	std::vector<VertexBuffer> MenueElementeBufferListe;

	std::vector<VertexBuffer> MapVertexBufferListe;
	std::vector<unsigned int> MapTexturIdListe;

	FpsKamera FpsKamera1 = FpsKamera(90.0f, 800.0f, 600.0f);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 modelviewprojektion;

	int modelviewprojektionmatrixlocation, moduslocation;

public:
	Grafik();

	void ShaderEinrichten();

	void KameraEinrichten();

	void MapTexturenEinlesen();

	void TexturEinlesen(const char* pfad);

	void MVPUpdate();

	void DrawMapBuffer(int mapbufferindex, int texturindex);

	void DrawMenueBuffer(int menuebufferindex, int texturindex);

	void DrawVorschauBuffer(int texturindex);

};

