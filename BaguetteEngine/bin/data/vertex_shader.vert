#version 330

in vec4 position;
in vec4 color;

out vec4 frag_color;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;

void main()
{
    gl_Position = modelViewProjectionMatrix * model * position;

	frag_color = color;
}