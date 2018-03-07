#version 330

in vec4 position;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;

void main()
{
    gl_Position = modelViewProjectionMatrix * model * position;
}