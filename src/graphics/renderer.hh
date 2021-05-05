#ifndef RENDERER_HH
#define RENDERER_HH

#include <graphics/mesh.hh>
#include <graphics/shader.hh>
#include <graphics/vertexattrib.hh>

#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

struct SimpleRenderer
{

    // we would later need a unorderd map here for storing 
    // model transformation along with the vertex array
    std::vector<std::pair<VertexArray, Mesh>> vertexarrays;
    ShaderProgram program;

    // view matrix is also the camera matrix for most of the operations
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    bool enable_3d;

    SimpleRenderer() = default;
    SimpleRenderer(ShaderProgram _program, bool enable_3d = false, glm::mat4 _view_mat = glm::mat4(1.0f), glm::mat4 _projection_mat = glm::mat4(1.0f));

    void add_mesh_to_render(Mesh mesh);
    void draw();
};


#endif