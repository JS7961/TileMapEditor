#include "Menue.h"





Menue::Menue(Grafik& gf) : Grafik1(gf)
{



}

void Menue::MenueElementeInitialisieren()
{

	MenueElement menueelement1, Form, Tiles,EffektTiles,Form1,Form2,Form3,Tilesheet,EffektTilesheet;


	menueelement1.MenueElementInitialisieren(-1.0f, -1.0f, 0.9f, 2.0f, 0.5f, 3, 2, true,0,0,4);

	Form.MenueElementInitialisieren(-1.0f, -0.68f , 0.0f, 0.5f, 0.18f, 1, 3, true,1, 0, 4);
	Tiles.MenueElementInitialisieren(-1.0f, -0.84f, 0.0f, 0.5f, 0.16f, 0, 3, true,2, 0, 4);
	EffektTiles.MenueElementInitialisieren(-1.0f, -1.00f, 0.0f, 0.5f, 0.16f, 2, 3, true, 7, 0, 4);

	Form1.MenueElementInitialisieren(-0.45f, -0.875f, 0.0f, 0.25f, 0.25f, 0, 2, true,3, 0, 4);
	Form2.MenueElementInitialisieren(-0.15f, -0.875f, 0.0f, 0.25f, 0.25f, 1, 2, true,4, 0, 4);
	Form3.MenueElementInitialisieren( 0.15f, -0.875f, 0.0f, 0.25f, 0.25f, 2, 2, true,5, 0, 4);

	Tilesheet.MenueElementInitialisieren(-0.5f, -1.00f, 0.1f, 1.5f, 0.5f, 0, 0,1.0f,0.5f, false,6,0,4);

	EffektTilesheet.MenueElementInitialisieren(-0.5f, -1.00f, 0.1f, 1.5f, 0.5f, 0, 0, 1.0f, 1.0f, false, 8, 1, 5);

	MenueElementListe.push_back(menueelement1);
	MenueElementListe.push_back(Form);
	MenueElementListe.push_back(Tiles);	

	MenueElementListe.push_back(Form1);
	MenueElementListe.push_back(Form2);
	MenueElementListe.push_back(Form3);

	MenueElementListe.push_back(Tilesheet);

	MenueElementListe.push_back(EffektTiles);

	MenueElementListe.push_back(EffektTilesheet);

}

void Menue::KompletterKollisionsCheck(float xf, float yf)
{
	aktuellxf = xf;
	aktuellyf = yf;
	for (size_t i = 1; i < MenueElementListe.size(); i++)
	{		
		if (MenueElementListe[i].KollisionsCheck(xf, yf) == true && MenueElementListe[i].angezeigt == true)
		{
			MenueFunktionWaehlen(MenueElementListe[i].MenueFunktionsIndex);
			break;
		}
	}
}

void Menue::DrawMenueToBuffer()
{
	Grafik1.MenueElementeBufferListe[0].Bind();
	Grafik1.MenueElementeBufferListe[0].DeleteBuffer();

	Grafik1.MenueElementeBufferListe[1].Bind();
	Grafik1.MenueElementeBufferListe[1].DeleteBuffer();


	for (size_t i = 0; i < MenueElementListe.size(); i++)
	{
		if (MenueElementListe[i].angezeigt == true)
		{
			for (size_t k = 0; k < 6; k++)
			{
				//Grafik1.MenueElementeBuffer.vertexliste.push_back(MenueElementListe[i].ElementVertexe[k]);
				Grafik1.MenueElementeBufferListe[MenueElementListe[i].menuebufferindex].vertexliste.push_back(MenueElementListe[i].ElementVertexe[k]);
			}			
		}
	}

	//Grafik1.MenueElementeBuffer.VertexBufferErstellen();
	Grafik1.MenueElementeBufferListe[0].VertexBufferErstellen();
	if (Grafik1.MenueElementeBufferListe[1].vertexliste.size() > 0)
	{
		Grafik1.MenueElementeBufferListe[1].VertexBufferErstellen();
	}
	

}

void Menue::DrawMenue()
{
	Grafik1.DrawMenueBuffer(0,1);

	if (Grafik1.MenueElementeBufferListe[1].vertexliste.size() > 0)
	{
		Grafik1.DrawMenueBuffer(1, 2);
	}
}









void Menue::MenueFunktionWaehlen(int MenueFunktionsIndex)
{
	if (MenueFunktionsIndex == 1)
	{
		FormAuswahl();
	}
	if (MenueFunktionsIndex == 2)
	{
		TileAuswahl();
	}
	if (MenueFunktionsIndex == 3)
	{
		AenderungHorizontal();
	}
	if (MenueFunktionsIndex == 4)
	{
		AenderungVertikal();
	}
	if (MenueFunktionsIndex == 5)
	{
		AenderungHorizontalVertikal();
	}
	if (MenueFunktionsIndex == 6)
	{
		EinzelnesTileWaehlen();
	}
	if (MenueFunktionsIndex == 7)
	{
		EffektTileAuswahl();
	}
	if (MenueFunktionsIndex == 8)
	{
		EinzelnesEffektTileWaehlen();
	}

	DrawMenueToBuffer();
}


void Menue::EffektTileAuswahl()
{
	MenueElementListe[3].angezeigt = false;
	MenueElementListe[4].angezeigt = false;
	MenueElementListe[5].angezeigt = false;
	MenueElementListe[6].angezeigt = false;
	MenueElementListe[8].angezeigt = true;
}

void Menue::TileAuswahl()
{
	MenueElementListe[3].angezeigt = false;
	MenueElementListe[4].angezeigt = false;
	MenueElementListe[5].angezeigt = false;
	MenueElementListe[6].angezeigt = true;
	MenueElementListe[8].angezeigt = false;
}

void Menue::FormAuswahl()
{
	MenueElementListe[3].angezeigt = true;
	MenueElementListe[4].angezeigt = true;
	MenueElementListe[5].angezeigt = true;
	MenueElementListe[6].angezeigt = false;
	MenueElementListe[8].angezeigt = false;
}



void Menue::AenderungHorizontal()
{
	MapEditor1->aenderunghorizontal = true;
	MapEditor1->aenderungvertikal = false;
	EffektMap->aenderunghorizontal = true;
	EffektMap->aenderungvertikal = false;
}

void Menue::AenderungVertikal()
{
	MapEditor1->aenderunghorizontal = false;
	MapEditor1->aenderungvertikal = true;
	EffektMap->aenderunghorizontal = false;
	EffektMap->aenderungvertikal = true;
}

void Menue::AenderungHorizontalVertikal()
{
	MapEditor1->aenderunghorizontal = true;
	MapEditor1->aenderungvertikal = true;
	EffektMap->aenderunghorizontal = true;
	EffektMap->aenderungvertikal = true;
}

void Menue::EinzelnesTileWaehlen()
{
	float xsheet, ysheet,tilesizex,tilesizey,erg;
	int ix=0, iy=0,index=0;
	xsheet = aktuellxf - MenueElementListe[6].x;
	ysheet = aktuellyf - MenueElementListe[6].y;

	tilesizex = MenueElementListe[6].breite / 16;
	tilesizey = MenueElementListe[6].hoehe / 8;

	for (size_t i = 1; i <= 16; i++)
	{
		erg = i * tilesizex;
		if (erg > xsheet)
		{
			ix = i - 1;
			break;
		}
	}

	for (size_t i = 1; i <= 8; i++)
	{
		erg = i * tilesizey;
		if (erg > ysheet)
		{
			iy = i - 1;
			break;
		}
	}

	index = 16 * iy + ix;

	MapEditor1->tilewert = index;

}

void Menue::EinzelnesEffektTileWaehlen()
{
	float xsheet, ysheet, tilesizex, tilesizey, erg;
	int ix = 0, iy = 0, index = 0;
	xsheet = aktuellxf - MenueElementListe[8].x;
	ysheet = aktuellyf - MenueElementListe[8].y;

	tilesizex = MenueElementListe[8].breite / 10;
	tilesizey = MenueElementListe[8].hoehe / 10;

	for (size_t i = 1; i <= 10; i++)
	{
		erg = i * tilesizex;
		if (erg > xsheet)
		{
			ix = i - 1;
			break;
		}
	}

	for (size_t i = 1; i <= 10; i++)
	{
		erg = i * tilesizey;
		if (erg > ysheet)
		{
			iy = i - 1;
			break;
		}
	}

	index = 10 * iy + ix;

	EffektMap->tilewert = index;

}







