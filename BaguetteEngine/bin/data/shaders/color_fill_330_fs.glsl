// IFT3100H18 ~ color_fill_330_fs.glsl

#version 330

uniform sampler2D tex0;
uniform bool texturePresent;
uniform int lightNb;
uniform vec4 colorAmbient0;
uniform vec4 colorAmbient1;
uniform vec4 colorAmbient2;
uniform vec4 colorAmbient3;

in vec2 texCoordVarying;

out vec4 fragmentColor;

void main()
{
	if (!texturePresent)
	{
		fragmentColor = colorAmbient0;

		if (lightNb == 2)
		{
			fragmentColor += (colorAmbient1);
		}
		else if (lightNb == 3)
		{
			fragmentColor += (colorAmbient1);
			fragmentColor += (colorAmbient2);
		}
		else if (lightNb == 4)
		{
			fragmentColor += (colorAmbient1);
			fragmentColor += (colorAmbient2);
			fragmentColor += (colorAmbient3);
		}
	}
	else
		fragmentColor = texture(tex0, vec2(texCoordVarying.x, 1 - texCoordVarying.y));
}
