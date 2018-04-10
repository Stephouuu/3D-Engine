// IFT3100H18 ~ color_fill_330_fs.glsl

#version 330

uniform sampler2D tex0;
uniform bool texturePresent;
uniform int lightNb;
uniform vec4 lightColors[10];

in vec2 texCoordVarying;

out vec4 fragmentColor;

void main()
{
	if (!texturePresent)
	{
		fragmentColor = vec4(0.1);

		for (int i = 0; i < lightNb; ++i)
			fragmentColor += lightColors[i];
	}
	else
		fragmentColor = texture(tex0, vec2(texCoordVarying.x, 1 - texCoordVarying.y));
}
