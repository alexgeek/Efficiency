#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

out vec3 position;

void main(){
	position = vertexPosition_modelspace.xyz;
	gl_Position = vec4(vertexPosition_modelspace,1);
}

