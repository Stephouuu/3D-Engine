#version 330

uniform sampler2D tex0; // portal sprite
uniform sampler2D tex1; // camera

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
	vec4 t0 = texture(tex0, vec2(texCoordVarying.x, 1 - texCoordVarying.y));
	vec4 t1 = texture(tex1, vec2(texCoordVarying.x, 1 - texCoordVarying.y));
	
	if (t0 == vec4(0, 0, 0, 1)) {
		outputColor = t1;
	} else {
		if (t0.a == 0) outputColor = vec4(0, 0, 0, 0);
		else outputColor = vec4(t0.rgb, 1);
	}
}