
#pragma once

#include <iostream>

#include "windows.h"

#define GLEW_STATIC

#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "VertexBuffer.h"
#include "Schatten.h"
#include "IndexBuffer.h"

#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "glm.hpp"
#include "ext/matrix_transform.hpp"
#include "gtc/matrix_transform.hpp"
#include <vector>
#include <filesystem>



#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#define DEFAULT_EXTENSION L".obj"


#include "MapEditor.h"
#include "Menue.h"
#include "Vorschau.h"

int FensterBreite = 1000;
int FensterHoehe = 1000;

void KoordinatenUmrechnen(int x, int y, float* xf, float* yf);
void MapSpeicherVorgang(MapEditor& m1, MapEditor& m2);
void MapLadeVorgang(MapEditor& m1, MapEditor& m2);
std::wstring SaveFileDialog();
std::wstring OpenFileDialog();
void DatenPfadFinden();




int main(int argc , char** argv)
{
	DatenPfadFinden();
	
	std::cout << "\n  " << DatenPfad << "  \n " ;

	SDL_Window* window;
	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetSwapInterval(1);

	unsigned int flags = SDL_WINDOW_OPENGL; // | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP;


	window = SDL_CreateWindow(" TileMapEditor ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000 , flags );

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum err =glewInit();

	if (err != GLEW_OK)
	{

	}
		
	Grafik gf = Grafik();

	gf.ShaderEinrichten();
	gf.KameraEinrichten();
	gf.MapTexturenEinlesen();

	MapEditor* MapEditor1 = new MapEditor(gf,0,0,16,8,256,128,0.0,1.0f);

	MapEditor* EffektMap = new MapEditor(gf, 1, 2, 10, 10, 1000, 1000, 0.05f,0.5f);

	Menue Menue1 = Menue(gf);

	Vorschau* Vorschau1 = new Vorschau(gf,0,16,8,256,128,0.0f,1.0f);
	Vorschau* Vorschau2 = new Vorschau(gf, 2, 10, 10, 1000, 1000, 0.0f, 1.0f);


	Menue1.MapEditor1 = MapEditor1;
	Menue1.EffektMap = EffektMap;

	//MapEditor1->MapLaden();
	MapEditor1->DrawMapToBuffer();
	EffektMap->DrawMapToBuffer();

	EffektMap->mapangezeigt = false;

	Menue1.MenueElementeInitialisieren();
	Menue1.DrawMenueToBuffer();



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		float wert = 0;
		bool orto = false;
		float posx = 0.5f;
		float movex = 0.01f;

		const void* datarep = &posx;

		//SDL_SetRelativeMouseMode(SDL_TRUE);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		bool  mausbewegung,rmb;
		
		mausbewegung = false;
		rmb = false;

		unsigned int ButtonState = 0;
		unsigned int AbsoluteMausState = 0;
		
		int xrel = 0, yrel = 0, x = 0, y = 0;
		float xf = 0, yf = 0;

		const Uint8* state = SDL_GetKeyboardState(NULL);

	while (true)
	{		
		SDL_Event event1;
		while (SDL_PollEvent(&event1))
		{
			if (event1.type == SDL_QUIT)
			{
				goto ende;
			}
			else
			{
				if (event1.type == SDL_KEYDOWN)
				{
					switch (event1.key.keysym.sym)
					{
					case SDLK_F5:
						MapSpeicherVorgang(*MapEditor1,*EffektMap);
						break;
					case SDLK_F9:
						MapLadeVorgang(*MapEditor1, *EffektMap);
						MapEditor1->DrawMapToBuffer();
						EffektMap->DrawMapToBuffer();
						break;
					
					default:
						break;
					}



					if (EffektMap->mapangezeigt == true)
					{
						switch (event1.key.keysym.sym)
						{
						case SDLK_t:
							EffektMap->TileWertSetzen(-1);
							break;
						case SDLK_z:
							EffektMap->TileWertSetzen(1);
							break;
						case SDLK_p:
							EffektMap->AenderungXYSetzen(1, 1);
							break;
						case SDLK_o:
							EffektMap->AenderungXYSetzen(-1, -1);
							break;
						case SDLK_e:
							EffektMap->MapAnzeigestatusAendern();
							break;

						default:
							break;
						}
					}
					else
					{
						switch (event1.key.keysym.sym)
						{
						case SDLK_t:
							MapEditor1->TileWertSetzen(-1);
							break;
						case SDLK_z:
							MapEditor1->TileWertSetzen(1);
							break;
						case SDLK_p:
							MapEditor1->AenderungXYSetzen(1, 1);
							break;
						case SDLK_o:
							MapEditor1->AenderungXYSetzen(-1, -1);
							break;
						case SDLK_e:
							EffektMap->MapAnzeigestatusAendern();
							break;

						default:
							break;
						}
					}

					
				}
												
			
			}
		}

		ButtonState = SDL_GetRelativeMouseState(&xrel , &yrel);

		if (ButtonState & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			AbsoluteMausState = SDL_GetMouseState(&x, &y);

			KoordinatenUmrechnen(x, y, &xf, &yf);

			//std::cout << "\n x: " << x << "  y: " << y << "    xf: " << xf << "  yf : " << yf;

			if (Menue1.MenueElementListe[0].KollisionsCheck(xf,yf) )
			{
				Menue1.KompletterKollisionsCheck(xf, yf);
			}
			else
			{
				if (EffektMap->mapangezeigt == true)
				{
					EffektMap->MapKollisionsCheck();
					EffektMap->TileAendern();
				}
				else
				{
					MapEditor1->MapKollisionsCheck();
					MapEditor1->TileAendern();
				}
			}
			
		}
			
		if (ButtonState & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			gf.FpsKamera1.MausBewegung(xrel, yrel);			
		}



		if (state[SDL_SCANCODE_W])
		{
			gf.FpsKamera1.FrontBewegung(1.0f);
		}

		if (state[SDL_SCANCODE_A])
		{
			gf.FpsKamera1.SeitenBewegung(-1.0f);
		}

		if (state[SDL_SCANCODE_S])
		{
			gf.FpsKamera1.FrontBewegung(-1.0f);
		}

		if (state[SDL_SCANCODE_D])
		{
			gf.FpsKamera1.SeitenBewegung(+1.0f);
		}

		if (state[SDL_SCANCODE_LCTRL])
		{
			gf.FpsKamera1.YBewegung(-1.0f);
		}

		if (state[SDL_SCANCODE_LSHIFT])
		{
			gf.FpsKamera1.YBewegung(1.0f);
		}



		if (EffektMap->mapangezeigt == true)
		{
			EffektMap->MapKollisionsCheck();
			Vorschau2->VorschauUpdate(EffektMap->tilekollisionx, EffektMap->tilekollisiony, EffektMap->tilewert, EffektMap->aenderungx, EffektMap->aenderungy);
		}
		else
		{
			MapEditor1->MapKollisionsCheck();
			Vorschau1->VorschauUpdate(MapEditor1->tilekollisionx, MapEditor1->tilekollisiony, MapEditor1->tilewert, MapEditor1->aenderungx, MapEditor1->aenderungy);
		}
		






		glClearColor( 0 , 0 , 0.5 , 1 );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*	movex = -0.002f;
		posx += movex;
		if (posx>10000)
		{
			posx = 0.5f;
		}*/

		

		gf.MVPUpdate();
		
		MapEditor1->DrawTileMap();
		EffektMap->DrawTileMap();

		Menue1.DrawMenue();


		if (EffektMap->mapangezeigt == true)
		{
			Vorschau2->DrawVorschau();
		}
		else
		{
			Vorschau1->DrawVorschau();
		}

		
	
		
		

		SDL_GL_SwapWindow(window);






		


	}

    ende:;

	return 0;
}

void KoordinatenUmrechnen(int x, int y, float* xf, float* yf)
{
	y = FensterHoehe - y;

	float quadrantenbreite = FensterBreite / 2;
	float quadrantenhoehe = FensterHoehe / 2;

	*xf = (float)((x - quadrantenbreite) / quadrantenbreite);

	*yf=  (float)((y - quadrantenhoehe) / quadrantenhoehe);

}

void MapSpeicherVorgang(MapEditor& m1, MapEditor& m2 )
{
	std::wstring pfad;

	pfad = SaveFileDialog(); //L"D:\\VisualStudioProjekte\\TileMapEditor\\map.dat";   //SaveFileDialog();

	

	if (pfad != L"")
	{
		
		unsigned short* werte1;
		unsigned short* werte2;

		werte1 = m1.MapSpeichern();
		werte2 = m2.MapSpeichern();

		std::ofstream  out(pfad, std::ios::out | std::ios::binary);
				
		for (size_t i = 0; i < 10000; i++)
		{
			out.write((char*)&werte1[i], sizeof(unsigned short));			
		}

		for (size_t i = 0; i < 10000; i++)
		{
			out.write((char*)&werte2[i], sizeof(unsigned short));
		}

		out.close();

		delete[] werte1;
		delete[] werte2;

	}
}

void MapLadeVorgang(MapEditor& m1, MapEditor& m2)
{
	std::wstring pfad;

	pfad = OpenFileDialog(); //L"D:\\VisualStudioProjekte\\TileMapEditor\\map.dat";   

	if (pfad != L"")
	{

		unsigned short* werte1 = new unsigned short[10000];
		unsigned short* werte2 = new unsigned short[10000];
		

		std::ifstream  in(pfad, std::ios::out | std::ios::binary);

		for (size_t i = 0; i < 10000; i++)
		{
			in.read((char*)&werte1[i], sizeof(unsigned short));
		}

		for (size_t i = 0; i < 10000; i++)
		{
			in.read((char*)&werte2[i], sizeof(unsigned short));
		}

		in.close();

		m1.MapLaden(werte1);
		m2.MapLaden(werte2);

		delete[] werte1;
		delete[] werte2;

	}
}





std::wstring SaveFileDialog()
{
	OPENFILENAME    ofn;
	const wchar_t* FilterSpec = L"Data(*.dat)\0*.dat\0Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0";
	const wchar_t* Title = L"Datei Speichern";
	wchar_t szFileName[MAX_PATH];
	wchar_t szFileTitle[MAX_PATH];
	int             Result;
	wchar_t filePath[MAX_PATH]; // Selected file and path

	*szFileName = 0;
	*szFileTitle = 0;

	/* fill in non-variant fields of OPENFILENAME struct. */
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetFocus();
	ofn.lpstrFilter = FilterSpec;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = L"."; // Initial directory.
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = Title;
	ofn.lpstrDefExt = DEFAULT_EXTENSION;

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (!GetSaveFileName((LPOPENFILENAME)&ofn))
	{
		wcscpy_s(filePath, L"");
	}
	else
	{
		wcscpy_s(filePath, ofn.lpstrFile);

	}

	std::wstring string1(filePath);

	return string1;

}

std::wstring OpenFileDialog()
{
	OPENFILENAME    ofn;
	const wchar_t* FilterSpec = L"Data(*.dat)\0*.dat\0Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0";
	const wchar_t* Title = L"Datei Oeffnen";
	wchar_t szFileName[MAX_PATH];
	wchar_t szFileTitle[MAX_PATH];
	int             Result;
	wchar_t filePath[MAX_PATH]; // Selected file and path

	*szFileName = 0;
	*szFileTitle = 0;

	/* fill in non-variant fields of OPENFILENAME struct. */
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetFocus();
	ofn.lpstrFilter = FilterSpec;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = L"."; // Initial directory.
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = Title;
	ofn.lpstrDefExt = DEFAULT_EXTENSION;

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (!GetOpenFileName((LPOPENFILENAME)&ofn))
	{
		wcscpy_s(filePath, L"");
	}
	else
	{
		wcscpy_s(filePath, ofn.lpstrFile);

	}

	std::wstring string1(filePath);

	return string1;

}


void DatenPfadFinden()
{
	wchar_t szPath[MAX_PATH];
	GetModuleFileNameW(NULL, szPath, MAX_PATH);

	std::filesystem::path pfad = std::filesystem::path{ szPath }.parent_path();

	std::string stringpath = pfad.generic_string();

	stringpath += "/";

	
	

	DatenPfad = stringpath;

}




