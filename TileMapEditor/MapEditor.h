#pragma once

#include "Grafik.h"


class MapEditor
{

	unsigned short TileMap[100][100];
public:
	int tilekollisionx, tilekollisiony, spriteanzahlx, spriteanzahly, spriteanzahl, spritebreite, spritehoehe, texturhoehe, texturbreite,texturindex,mapbufferindex;
	

public:

	bool aenderungvertikal, aenderunghorizontal,mapangezeigt;
	int aenderungx, aenderungy, tilewert;
	float rsx, rsy,z, transparenzwert;
	

	vertex v1, v2, v3, v4;



public:
	Grafik& Grafik1;

public:



	MapEditor(Grafik& gf,int mapbufferindex, int texturindex, int spriteanzahlx, int spriteanzahly, int texturbreite, int texturhoehe,float z, float transparenzwert);
	
	void MapInitialisieren();

	void DrawMapToBuffer();

	void TileVertexSetzen(int i, int j, int tx, int ty);

	void VertexeHinzufuegen();

	void DrawTileMap();

	void AenderungXYSetzen(int x,int y);

	void MapKollisionsCheck();

	void TileAendern();

	void TileWertSetzen(int aenderung);

	void MapAnzeigestatusAendern();

	unsigned short* MapSpeichern();

	void MapLaden(unsigned short* werte);

};

