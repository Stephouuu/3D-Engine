#version 330

uniform sampler2D tex0;
uniform bool texturePresent;

in vec4 out_color;
in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
	if (!texturePresent) outputColor = out_color;
	else outputColor = texture(tex0, vec2(texCoordVarying.x, 1 - texCoordVarying.y));
}