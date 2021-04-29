#version 330 core

layout(location = 0) in vec3 vertexposition;
layout(location = 1) in vec3 vertexnormal;

out vec3 outputnormal;

void main()
{
    gl_Position.xyz = vertexposition;
    gl_Position.w = 1.0f;
    outputnormal = vertexnormal;
}