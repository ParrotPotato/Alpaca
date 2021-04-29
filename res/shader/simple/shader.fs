#version 330 core

in vec3 outputnormal;
out vec4 color;

void main()
{
    color = vec4(outputnormal, 1.0);
}