#version 330 core

layout(location = 0) in vec3 vertexposition;

void main()
{
    gl_Position.xyz = vertexposition;
    gl_Position.w = 1.0f;
}