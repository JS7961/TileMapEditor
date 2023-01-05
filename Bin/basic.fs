#version 330 core

layout(location = 0) out vec4 fcolor;

in vec4 vcoloraus;
in vec2 vtexturaus;


uniform sampler2D utextur;
uniform vec4 ucolor;



void main()
{
//fcolor=vcoloraus;
//fcolor=vec4( 1.0 , 0 , 0 , 1 );



vec4 texcolor=texture(utextur, vtexturaus);
texcolor.w=vcoloraus.w;
fcolor=texcolor;

//fcolor=ucolor;
}