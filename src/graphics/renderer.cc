#include <graphics/renderer.hh>

SimpleRenderer::SimpleRenderer(ShaderProgram _program):program(_program)
{
    // do something with this
}

void SimpleRenderer::add_mesh_to_render(Mesh mesh)
{
    RenderBuffer render_buffer(mesh);
    VertexArray vertex_array(render_buffer);
    vertexarrays.push_back(vertex_array);
}

void SimpleRenderer::draw()
{
    glUseProgram(program.programid);
    for(auto vertexarr : vertexarrays)
    {
        vertexarr.bind_and_render();
    }
    glUseProgram(0);
}