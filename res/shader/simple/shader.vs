#version 330 core

layout(location = 0) in vec3 vertexposition;
layout(location = 1) in vec3 vertexnormal;
layout(location = 2) in vec2 vertextexcoord;

out vec3 outputnormal;
out vec2 fragmenttexcoord;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

void main()
{
    gl_Position = projection * view * model * vec4(vertexposition, 1.0f);
    outputnormal = vertexnormal;
    fragmenttexcoord = vertextexcoord;
}
