#include <graphics/renderer.hh>

#include <glm/gtc/type_ptr.hpp>

#include <utility>

SimpleRenderer::SimpleRenderer(ShaderProgram _program, glm::mat4 _view_mat, glm::mat4 _projection_mat):program(_program),view_matrix(_view_mat),projection_matrix(_projection_mat)
{
    // do something with this
}

void SimpleRenderer::add_mesh_to_render(Mesh mesh)
{
    RenderBuffer render_buffer(mesh);
    VertexArray vertex_array(render_buffer);
    vertexarrays.push_back(std::make_pair(vertex_array, mesh.model_mat));
}

void SimpleRenderer::draw()
{
    glUseProgram(program.programid);
    for(std::pair<VertexArray, glm::mat4> entry: vertexarrays)
    {
        auto vertexarr = entry.first;
        auto model_mat = entry.second;

        if(program.shaderinfo.model_mat)
            glUniformMatrix4fv(program.model_mat_location, 1, GL_FALSE, glm::value_ptr(model_mat));
        if(program.shaderinfo.view_mat)
            glUniformMatrix4fv(program.view_mat_location, 1, GL_FALSE, glm::value_ptr(view_matrix));
        if(program.shaderinfo.projection_mat)
            glUniformMatrix4fv(program.projection_mat_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        //vertexarr.bind_and_render();
        glBindVertexArray(vertexarr.id);
        glDrawElements(GL_TRIANGLES, vertexarr.renderbuffer.triangle_count * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}