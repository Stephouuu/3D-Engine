#version 330

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;

void main()
{
    gl_Position = modelViewProjectionMatrix * model * position;
	texCoordVarying = texcoord;
}