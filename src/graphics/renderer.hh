#ifndef RENDERER_HH
#define RENDERER_HH

#include <graphics/mesh.hh>
#include <graphics/shader.hh>
#include <graphics/vertexattrib.hh>

#include <vector>
#include <unordered_map>

struct SimpleRenderer
{

    // we would later need a unorderd map here for storing 
    // model transformation along with the vertex array
    std::vector<VertexArray> vertexarrays;
    ShaderProgram program;

    SimpleRenderer() = default;
    SimpleRenderer(ShaderProgram _program);

    void add_mesh_to_render(Mesh mesh);
    void draw();
};


#endif