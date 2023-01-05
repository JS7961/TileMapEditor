#pragma once

#include "Grafik.h"


class Vorschau
{

public:

	Grafik& Grafik1;

	vertex v1, v2, v3, v4;

	int aenderungx, aenderungy, tilewert, tilekollisionx, tilekollisiony,spriteanzahlx , spritebreite, spritehoehe, texturhoehe, texturbreite,texturindex;

	float rsx, rsy;

public:

	Vorschau(Grafik& gf, int texturindex, int spriteanzahlx, int spriteanzahly, int texturbreite, int texturhoehe, float z, float transparenzwert);

	void VorschauUpdate(int tilekollisionx ,int tilekollisiony, int tilewert, int aenderungx, int aenderungy);

	void DrawVorschauToBuffer();

	void TileVertexSetzen(int i, int j, int tx, int ty);

	void VertexeHinzufuegen();

	void DrawVorschau();

};

