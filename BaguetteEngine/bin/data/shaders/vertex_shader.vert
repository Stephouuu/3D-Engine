#version 330

in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec2 texCoordVarying;
out vec4 out_color;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;

void main()
{
    gl_Position = modelViewProjectionMatrix * model * position;
	out_color = color;
	texCoordVarying = texcoord;
}