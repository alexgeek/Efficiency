#version 330 core

out vec4 color;
in vec3 position;

// Values that stay constant for the whole mesh.
uniform samplerCube tex;

void main() {
	// Output color = color of the texture at the specified UV
	color = texture(tex, position);
}
