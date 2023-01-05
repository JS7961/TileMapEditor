#version 330 core

 layout(location = 0) in vec3 position;
 layout(location = 1) in vec4 vcolor;
 layout(location = 2) in vec2 vtextur;

out vec4 vcoloraus;
out vec2 vtexturaus;

uniform mat4 umodelviewprojektion;

uniform int umodus;

void main()
{
if(umodus == 1)
{
 gl_Position = umodelviewprojektion * vec4(position, 1.0f );
}

if(umodus == 2)
{
 gl_Position =  vec4(position, 1.0f );
}


vcoloraus=vcolor;
vtexturaus=vtextur;
}