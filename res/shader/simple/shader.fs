#version 330 core

in vec3 outputnormal;
in vec2 fragmenttexcoord;

uniform sampler2D meshtexture;

out vec4 color;

void main()
{
    color = texture(meshtexture, fragmenttexcoord);
    color.a = 1.0f;
}
