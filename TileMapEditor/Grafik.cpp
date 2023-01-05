#include "Grafik.h"


#include "stb_image.h"

Grafik::Grafik()
{
	VertexBuffer vb1 = VertexBuffer();

	MapVertexBufferListe.push_back(vb1);

	MapVertexBufferListe.push_back(vb1);

	MenueElementeBufferListe.push_back(vb1);
	MenueElementeBufferListe.push_back(vb1);
}

void Grafik::ShaderEinrichten()
{
	Schatten1.SchattenEinlesen(DatenPfad);
	Schatten1.Bind();

}

void Grafik::KameraEinrichten()
{

	/*Kamera Kamera1 = Kamera(90.0f, 800.0f, 600.0f);
	Kamera1.KameraBewegen(glm::vec3(0.0f, 0.0f, 5.0f));
	Kamera1.KameraUpdate();*/

    //FpsKamera1 = FpsKamera(90.0f, 800.0f, 600.0f);
	FpsKamera1.KameraBewegen(glm::vec3(0.0f, 0.0f, 5.0f));
	FpsKamera1.KameraUpdate();


	model = glm::scale(model, glm::vec3(1.0f));

	modelviewprojektionmatrixlocation = glGetUniformLocation(Schatten1.GetShaderid(), "umodelviewprojektion");

}

void Grafik::MapTexturenEinlesen()
{
	//TexturEinlesen("D:\\VisualStudioProjekte\\TileMapEditor\\Start.png");

	//TexturEinlesen("Start.png");
	//TexturEinlesen("Menue.png");
	//TexturEinlesen("Effekt.png");

	std::string p1,p2,p3;

	p1 = DatenPfad + "Start.png";
	TexturEinlesen( p1.c_str() );

	p2 = DatenPfad + "Menue.png";
	TexturEinlesen(p2.c_str());

	p3 = DatenPfad + "Effekt.png";
	TexturEinlesen(p3.c_str());
		

	int uniformfarbe = glGetUniformLocation(Schatten1.GetShaderid(), "ucolor");

	glUniform4f(uniformfarbe, 1.0f, 0.0f, 1.0f, 1.0f);

	moduslocation = glGetUniformLocation(Schatten1.GetShaderid(), "umodus");
	glUniform1i(moduslocation, 1);


	int texturuniform = glGetUniformLocation(Schatten1.GetShaderid(), "utextur");
	glUniform1i(texturuniform, 0);
}

void Grafik::TexturEinlesen(const char* pfad)
{
	int breite = 2, hoehe = 5, bitspropixel = 0;

	stbi_set_flip_vertically_on_load(true);
	
	auto texturebuffer = stbi_load(pfad, &breite, &hoehe, &bitspropixel, 4);  

	//std::cout << "\n  groesse:  " << breite << "   " << hoehe;

	unsigned int textureid;
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, breite, hoehe, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturebuffer);
	glBindTexture(GL_TEXTURE_2D, textureid);

	MapTexturIdListe.push_back(textureid);




}

void Grafik::MVPUpdate()
{
	FpsKamera1.KameraUpdate();
	modelviewprojektion = FpsKamera1.GetProjektionview() * model;

	glUniformMatrix4fv(modelviewprojektionmatrixlocation, 1, GL_FALSE, &modelviewprojektion[0][0]);
}

void Grafik::DrawMapBuffer(int mapbufferindex, int texturindex)
{
	/*FpsKamera1.KameraUpdate();
	modelviewprojektion = FpsKamera1.GetProjektionview() * model;

	glUniformMatrix4fv(modelviewprojektionmatrixlocation, 1, GL_FALSE, &modelviewprojektion[0][0]);*/

	glUniform1i(moduslocation, 1);

	
		MapVertexBufferListe[mapbufferindex].Bind();
		glBindTexture(GL_TEXTURE_2D, MapTexturIdListe[texturindex]);
		glDrawArrays(GL_TRIANGLES , 0, MapVertexBufferListe[mapbufferindex].vertexliste.size() );
	

	MapVertexBufferListe[mapbufferindex].UnBind();

}

void Grafik::DrawMenueBuffer(int menuebufferindex, int texturindex)
{
	glUniform1i(moduslocation, 2);

	MenueElementeBufferListe[menuebufferindex].Bind();
	glBindTexture(GL_TEXTURE_2D, MapTexturIdListe[texturindex]);
	glDrawArrays(GL_TRIANGLES, 0, MenueElementeBufferListe[menuebufferindex].vertexliste.size());
	MenueElementeBufferListe[menuebufferindex].UnBind();

}

void Grafik::DrawVorschauBuffer(int texturindex)
{
	glUniform1i(moduslocation, 1);

	VorschauBuffer.Bind();
	glBindTexture(GL_TEXTURE_2D, MapTexturIdListe[texturindex]);
	glDrawArrays(GL_TRIANGLES, 0,  VorschauBuffer.vertexliste.size());
	VorschauBuffer.UnBind();
}
