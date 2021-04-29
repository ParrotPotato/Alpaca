#ifndef MESH_HH
#define MESH_HH

#include <glm/glm.hpp>

#include <vector>

// NOTE(nitesh) : We are not storing the world level transformation 
// in the model structure, figure out how to do that.

struct Mesh
{
    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<int> indices;
};

#endif