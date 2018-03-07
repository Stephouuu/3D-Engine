/* #version 400

in vec3 in_vertex;
in vec3 in_color;

// uniform vec3 in_color;
// uniform vec3 in_vertex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 color;

void main() {
	// P x V x M
	gl_Position = projection * view * model * vec4(in_vertex, 1.0);
	color = in_color;
} */

#version 400

uniform mat4 mvp;
in vec4 position;

void main(){
    gl_Position = mvp * position;
}