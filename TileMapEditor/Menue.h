#pragma once


#include "Grafik.h"

#include "MapEditor.h"


class MenueElement
{

public:

	int texturindex,menuebufferindex,MenueFunktionsIndex;
	bool angezeigt;
	float x, y, z, breite, hoehe;
	
	//void (*ElementFunktion)(std::vector<MenueElement>);

	

	std::array<vertex, 6> ElementVertexe;

	

	

	void MenueElementInitialisieren(float x, float y, float z, float breite, float hoehe,int tilespriteindexX, int tilespriteindexY, bool angezeigt,int MenueFunktionsIndex, int menuebufferindex, int texturindex)
	{
		texturindex = 4;
		MenueElement::angezeigt = angezeigt;
		MenueElement::MenueFunktionsIndex = MenueFunktionsIndex;
		MenueElement::texturindex = texturindex;
		MenueElement::menuebufferindex = menuebufferindex;

		MenueElement::x = x;
		MenueElement::y = y;
		MenueElement::z = z;
		MenueElement::breite = breite;
		MenueElement::hoehe = hoehe;


		vertex v1, v2, v3, v4;

		float px, py, rsx, rsy;

		rsx = 0.25;
		rsy = 0.25;

		px = rsx * tilespriteindexX;
		py = rsy * tilespriteindexY;

		v1.x = x;
		v1.y = y;
		v1.z = z;
		v1.u = px;
		v1.v = py;
		v1.a = 1.0f;

		v2.x = v1.x + breite;
		v2.y = v1.y;
		v2.z = z;
		v2.u = px + rsx;
		v2.v = py;
		v2.a = 1.0f;

		v3.x = v1.x;
		v3.y = v1.y + hoehe;
		v3.z = z;
		v3.u = px;
		v3.v = py + rsy;
		v3.a = 1.0f;

		v4.x = v1.x + breite;
		v4.y = v1.y + hoehe;
		v4.z = z;
		v4.u = px + rsx;
		v4.v = py + rsy;
		v4.a = 1.0f;

		ElementVertexe[0] = v1;
		ElementVertexe[1] = v2;
		ElementVertexe[2] = v3;

		ElementVertexe[3] = v2;
		ElementVertexe[4] = v3;
		ElementVertexe[5] = v4;
	}

	void MenueElementInitialisieren(float x, float y, float z, float breite, float hoehe, int tilespriteindexX, int tilespriteindexY,float tilespritesizeX , float tilespritesizeY,bool angezeigt, int MenueFunktionsIndex, int menuebufferindex, int texturindex)
	{
		texturindex = 4;
		MenueElement::angezeigt = angezeigt;
		MenueElement::MenueFunktionsIndex = MenueFunktionsIndex;
		MenueElement::texturindex = texturindex;
		MenueElement::menuebufferindex = menuebufferindex;

		MenueElement::x = x;
		MenueElement::y = y;
		MenueElement::z = z;
		MenueElement::breite = breite;
		MenueElement::hoehe = hoehe;



		vertex v1, v2, v3, v4;

		float px, py, rsx, rsy;

		rsx = tilespritesizeX;
		rsy = tilespritesizeY;

		px = rsx * tilespriteindexX;
		py = rsy * tilespriteindexY;

		v1.x = x;
		v1.y = y;
		v1.z = z;
		v1.u = px;
		v1.v = py;
		v1.a = 1.0f;

		v2.x = v1.x + breite;
		v2.y = v1.y;
		v2.z = z;
		v2.u = px + rsx;
		v2.v = py;
		v2.a = 1.0f;

		v3.x = v1.x;
		v3.y = v1.y + hoehe;
		v3.z = z;
		v3.u = px;
		v3.v = py + rsy;
		v3.a = 1.0f;

		v4.x = v1.x + breite;
		v4.y = v1.y + hoehe;
		v4.z = z;
		v4.u = px + rsx;
		v4.v = py + rsy;
		v4.a = 1.0f;

		ElementVertexe[0] = v1;
		ElementVertexe[1] = v2;
		ElementVertexe[2] = v3;

		ElementVertexe[3] = v2;
		ElementVertexe[4] = v3;
		ElementVertexe[5] = v4;
	}

	bool KollisionsCheck(float xf, float yf)
	{
		if ( xf >= x && xf <= (x+breite) )
		{
			if ( yf >= y && yf <= (y + hoehe) )
			{
				return true;
			}
		}
		return false;
	}

};


class Menue
{

public:
	Grafik& Grafik1;
	MapEditor* MapEditor1;
	MapEditor* EffektMap;

	std::vector<MenueElement> MenueElementListe;

	float aktuellxf, aktuellyf;

public:



	Menue(Grafik& gf);

	void MenueElementeInitialisieren();

	void KompletterKollisionsCheck(float xf, float yf);

	void DrawMenueToBuffer();

	void DrawMenue();


	void MenueFunktionWaehlen(int MenueFunktionsIndex);

	void EffektTileAuswahl();
	void TileAuswahl();
	void FormAuswahl();
	void AenderungHorizontal();
	void AenderungVertikal();
	void AenderungHorizontalVertikal();
	void EinzelnesTileWaehlen();
	void EinzelnesEffektTileWaehlen();
	




};





