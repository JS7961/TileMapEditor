#include "Vorschau.h"



Vorschau::Vorschau(Grafik& gf, int texturindex, int spriteanzahlx, int spriteanzahly, int texturbreite, int texturhoehe, float z, float transparenzwert) : Grafik1(gf)
{
	aenderungx = 1;
	aenderungy = 1;
	tilewert = 0;
	tilekollisionx = 0;
	tilekollisiony = 0;

	

	Vorschau::spriteanzahlx = spriteanzahlx;
	

	Vorschau::texturbreite = texturbreite;
	Vorschau::texturhoehe = texturhoehe;

	spritebreite = texturbreite / spriteanzahlx;
	spritehoehe = texturhoehe / spriteanzahly;
	
	Vorschau::texturindex = texturindex;

	rsx = ((float)spritebreite / (float)texturbreite);
	rsy = ((float)spritehoehe / (float)texturhoehe);
}

void Vorschau::VorschauUpdate(int tilekollisionx, int tilekollisiony, int tilewert, int aenderungx, int aenderungy)
{
	
	if (Vorschau::aenderungx != aenderungx || Vorschau::aenderungy != aenderungy || Vorschau::tilewert != tilewert || Vorschau::tilekollisionx != tilekollisionx || Vorschau::tilekollisiony != tilekollisiony)
	{
		Vorschau::aenderungx = aenderungx;
		Vorschau::aenderungy = aenderungy;
		Vorschau::tilewert = tilewert;
		Vorschau::tilekollisionx = tilekollisionx;
		Vorschau::tilekollisiony = tilekollisiony;

		DrawVorschauToBuffer();
	}

}

void Vorschau::DrawVorschauToBuffer()
{
	Grafik1.VorschauBuffer.Bind();
	Grafik1.VorschauBuffer.DeleteBuffer();

	int endex, endey,tx,ty;

	int test;

	test = aenderungx + tilekollisionx;

	if (test > 100)
	{
		test = 100;
	}

	endex = test;

	test = tilekollisiony - aenderungy;

	if (test < -1)
	{
		test = -1;
	}

	endey = test;

	tx = tilewert % spriteanzahlx;
	ty = tilewert / spriteanzahlx;

	for (int j = tilekollisiony; j > endey; j--)
	{
		for (int i = tilekollisionx; i < endex; i++)
		{
			TileVertexSetzen(i, j, tx, ty);
			VertexeHinzufuegen();
		}
	}

	Grafik1.VorschauBuffer.VertexBufferErstellen();
}

void Vorschau::TileVertexSetzen(int i, int j, int tx, int ty)
{
	float px, py;

	px = rsx * tx;
	py = rsy * ty;

	v1.x = i * 1.0f;
	v1.y = j * 1.0f;
	v1.z = 0.1f;
	v1.u = px;
	v1.v = py;
	v1.a = 1.0f;

	v2.x = v1.x + 1.0f;
	v2.y = v1.y;
	v2.z = 0.1f;
	v2.u = px + rsx;
	v2.v = py;
	v2.a = 1.0f;

	v3.x = v1.x;
	v3.y = v1.y + 1.0f;
	v3.z = 0.1f;
	v3.u = px;
	v3.v = py + rsy;
	v3.a = 1.0f;

	v4.x = v1.x + 1.0f;
	v4.y = v1.y + 1.0f;
	v4.z = 0.1f;
	v4.u = px + rsx;
	v4.v = py + rsy;
	v4.a = 1.0f;
}

void Vorschau::VertexeHinzufuegen()
{
	Grafik1.VorschauBuffer.vertexliste.push_back(v1);
	Grafik1.VorschauBuffer.vertexliste.push_back(v2);
	Grafik1.VorschauBuffer.vertexliste.push_back(v3);

	Grafik1.VorschauBuffer.vertexliste.push_back(v2);
	Grafik1.VorschauBuffer.vertexliste.push_back(v3);
	Grafik1.VorschauBuffer.vertexliste.push_back(v4);
}

void Vorschau::DrawVorschau()
{
	Grafik1.DrawVorschauBuffer(texturindex);
}


