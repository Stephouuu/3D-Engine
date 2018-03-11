#version 330

uniform sampler2DRect tex0;

in vec4 out_color;
out vec4 outputColor;

void main() {
	outputColor = out_color;
	// outputColor = texture(tex0, texCoordVarying);
}
