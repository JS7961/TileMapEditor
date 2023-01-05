#include "MapEditor.h"





MapEditor::MapEditor(Grafik& gf, int mapbufferindex, int texturindex,int spriteanzahlx,int spriteanzahly,int texturbreite,int texturhoehe,float z,float transparenzwert) : Grafik1(gf)
{
	

	tilekollisionx = 0;
	tilekollisiony = 0;

	MapEditor::spriteanzahlx = spriteanzahlx;
	MapEditor::spriteanzahly = spriteanzahly;

	spriteanzahl = spriteanzahlx * spriteanzahly;

	MapEditor::texturbreite = texturbreite;
	MapEditor::texturhoehe = texturhoehe;

	spritebreite = texturbreite/spriteanzahlx;
	spritehoehe = texturhoehe/spriteanzahly;

	MapEditor::mapbufferindex = mapbufferindex;
	MapEditor::texturindex = texturindex;

	aenderungx = 1;
	aenderungy = 1;

	tilewert = 0;

	aenderunghorizontal = true;
	aenderungvertikal = true;
	mapangezeigt = true;

	rsx = ((float)spritebreite / (float)texturbreite);
	rsy = ((float)spritehoehe / (float)texturhoehe);

	MapEditor::z = z;
	MapEditor::transparenzwert = transparenzwert;

	MapInitialisieren();

}

void MapEditor::MapInitialisieren()
{
	for (size_t j = 0; j < 100; j++)
	{
		for (size_t i = 0; i < 100; i++)
		{
			TileMap[j][i] = 3;
		}
	}

	for (size_t j = 0; j < 10; j++)
	{
		for (size_t i = 0; i < 10; i++)
		{
			TileMap[j][i] = 0;
		}
	}

	for (size_t j = 5; j < 8; j++)
	{
		for (size_t i = 5; i < 8; i++)
		{
			TileMap[j][i] = 1;
		}
	}

	for (size_t j = 0; j < 10; j++)
	{
		for (size_t i = 2; i < 3; i++)
		{
			TileMap[j][i] = 2;
		}
	}


}

void MapEditor::DrawMapToBuffer()
{
	Grafik1.MapVertexBufferListe[mapbufferindex].Bind();
	Grafik1.MapVertexBufferListe[mapbufferindex].DeleteBuffer();

	//Grafik1.MapVertexBufferListe.clear();


	//VertexBuffer vb1 = VertexBuffer();


	//Grafik1.MapVertexBufferListe.push_back(vb1);
	

	for (size_t j = 0; j < 100; j++)
	{
		for (size_t i = 0; i < 100; i++)
		{
			
			TileVertexSetzen(i, j, TileMap[j][i]%spriteanzahlx, TileMap[j][i] / spriteanzahlx);
			VertexeHinzufuegen();
						
		}
	}

	Grafik1.MapVertexBufferListe[mapbufferindex].VertexBufferErstellen();


}


void MapEditor::TileVertexSetzen(int i, int j, int tx,int ty)
{
	float px, py;
	
	px = rsx * tx;
	py = rsy * ty;

	v1.x = i * 1.0f;
	v1.y = j * 1.0f;
	v1.z = z;
	v1.u = px;
	v1.v = py;
	v1.a = transparenzwert;

	v2.x = v1.x + 1.0f;
	v2.y = v1.y;
	v2.z = z;
	v2.u = px+rsx;
	v2.v = py;
	v2.a = transparenzwert;

	v3.x = v1.x;
	v3.y = v1.y + 1.0f;
	v3.z = z;
	v3.u = px;
	v3.v = py+rsy;
	v3.a = transparenzwert;

	v4.x = v1.x + 1.0f;
	v4.y = v1.y + 1.0f;
	v4.z = z;
	v4.u = px+rsx;
	v4.v = py+rsy;
	v4.a = transparenzwert;


}


void MapEditor::VertexeHinzufuegen()
{
	Grafik1.MapVertexBufferListe[mapbufferindex].vertexliste.push_back(v1);
	Grafik1.MapVertexBufferListe[mapbufferindex].vertexliste.push_back(v2);
	Grafik1.MapVertexBufferListe[mapbufferindex].vertexliste.push_back(v3);

	Grafik1.MapVertexBufferListe[mapbufferindex].vertexliste.push_back(v2);
	Grafik1.MapVertexBufferListe[mapbufferindex].vertexliste.push_back(v3);
	Grafik1.MapVertexBufferListe[mapbufferindex].vertexliste.push_back(v4);
}


void MapEditor::DrawTileMap()
{
	if (mapangezeigt == true)
	{
		Grafik1.DrawMapBuffer(mapbufferindex, texturindex);
	}	
}

void MapEditor::TileWertSetzen(int aenderung)
{
	int test;

	test = tilewert + aenderung;

	if (test >= spriteanzahl)
	{
		test = spriteanzahl-1;
	}

	if (test < 0)
	{
		test = 0;
	}

	tilewert = test;
}

void MapEditor::MapAnzeigestatusAendern()
{
	if (MapEditor::mapangezeigt == true)
	{
		MapEditor::mapangezeigt = false;
	}
	else
	{
		MapEditor::mapangezeigt = true;
	}
}

unsigned short* MapEditor::MapSpeichern()
{
	unsigned short* werte = new unsigned short[10000];
	int index = 0;

	for (size_t j = 0; j < 100; j++)
	{
		for (size_t i = 0; i < 100; i++)
		{
			werte[index] = TileMap[j][i];
			index++;
		}
	}

	return werte;
}

void MapEditor::MapLaden(unsigned short* werte)
{	
	int index = 0;

	for (size_t j = 0; j < 100; j++)
	{
		for (size_t i = 0; i < 100; i++)
		{
			TileMap[j][i] = werte[index];
			index++;
		}
	}

	
}

void MapEditor::TileAendern()
{
	int endex,endey;
	
	int test;

	test = aenderungx + tilekollisionx;

	if (test > 100)
	{
		test = 100;
	}
	
	endex = test;

	test = tilekollisiony - aenderungy ;

	if (test < -1)
	{
		test = -1;
	}

	endey = test;



	for (int j = tilekollisiony; j > endey; j--)
	{
		for (int i = tilekollisionx; i < endex; i++)
		{
			TileMap[j][i] = tilewert;
		}
	}

	//TileMap[tilekollisiony][tilekollisionx] = tilewert;

	//Grafik1.MapVertexBufferListe.clear();

/*	Grafik1.MapVertexBufferListe[0].Bind();
	Grafik1.MapVertexBufferListe[0].DeleteBuffer();

	Grafik1.MapVertexBufferListe.clear();*/

	DrawMapToBuffer();


	/*if (tilewert == 0)
	{
		TileVertexSetzen(i, j, 0, 0);
		VertexeHinzufuegen();
	}

	if (tilewert == 1)
	{
		TileVertexSetzen(i, j, 3, 2);
		VertexeHinzufuegen();
	}

	if (tilewert] == 2)
	{
		TileVertexSetzen(i, j, 1, 4);
		VertexeHinzufuegen();
	}

	if (tilewert == 3)
	{
		TileVertexSetzen(i, j, 2, 3);
		//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex) * 9, 4, datarep);
	}*/

}

void MapEditor::AenderungXYSetzen(int x, int y)
{
	int test;

	if (aenderunghorizontal == true)
	{
		test = aenderungx + x;

		if (test > 100)
		{
			test = 100;
		}

		if (test < 1)
		{
			test = 1;
		}

		aenderungx = test;
	}

	if (aenderungvertikal == true)
	{

		test = aenderungy + y;

		if (test > 100)
		{
			test = 100;
		}

		if (test < 1)
		{
			test = 1;
		}

		aenderungy = test;

	}
	
}


void MapEditor::MapKollisionsCheck()
{
	float lz, pz;
	glm::vec3 erg;

	lz = Grafik1.FpsKamera1.lookat.z;
	pz = Grafik1.FpsKamera1.position.z;

	erg = Grafik1.FpsKamera1.position + ((-pz)/lz) * Grafik1.FpsKamera1.lookat;

	if (erg.x >= 0 && erg.x < 100 && erg.y >= 0 && erg.y < 100)
	{
		tilekollisionx = erg.x;
		tilekollisiony = erg.y;
	}
	


}




