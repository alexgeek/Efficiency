#version 330 core

out vec4 color;
in vec3 position;

// Values that stay constant for the whole mesh.
uniform samplerCube tex;
uniform float globaltime;

void main( void )
{
	color = texture(tex, position);
}

