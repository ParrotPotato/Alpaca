#ifndef MESH_HH
#define MESH_HH

#include <graphics/texture.hh>

#include <glm/glm.hpp>

#include <vector>

// NOTE(nitesh) : We are not storing the world level transformation 
// in the model structure, figure out how to do that.

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex() = default;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    Texture texture;

    glm::mat4 model_mat = glm::mat4(1.0f);
};

#endif