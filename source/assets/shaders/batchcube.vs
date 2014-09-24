#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 WorldPosition;

uniform mat4 MV;
flat out int InstanceID;

out vec3 position;

void main(){
	position = vertexPosition.xyz;
	gl_Position =  MV * vec4(position + WorldPosition,1);
	InstanceID = gl_InstanceID;
}

