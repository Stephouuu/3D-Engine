// IFT3100H18 ~ color_fill_330_vs.glsl

#version 330

// attribut de sommet
in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec2 texCoordVarying;
out vec4 out_color;

// attributs uniformes

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;

void main()
{
  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = modelViewProjectionMatrix * model * position;
  out_color = color;
  texCoordVarying = texcoord;
}