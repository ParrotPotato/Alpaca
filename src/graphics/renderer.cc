#include <graphics/renderer.hh>

#include <glm/gtc/type_ptr.hpp>

#include <utility>

SimpleRenderer::SimpleRenderer(ShaderProgram _program, bool enable_3d, glm::mat4 _view_mat, glm::mat4 _projection_mat):program(_program),view_matrix(_view_mat),projection_matrix(_projection_mat)
{
    if(enable_3d == false)
    {
        // setting up ortho graphic projection if the rendering is set to be 2d (which is not entirely accurate but
        // works for now)
        projection_matrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    }
    else
    {
        // setting up perspective projection if the rendering is set to be 3d (meh, kind of a hack (with all the aspect ratio)
        // but works for the time being)
        projection_matrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    }
}

void SimpleRenderer::add_mesh_to_render(Mesh mesh)
{
    RenderBuffer render_buffer(mesh);
    VertexArray vertex_array(render_buffer);
    vertexarrays.push_back(std::make_pair(vertex_array, mesh));
    // This leads to creating a copy of the entire mesh along with the texture reference
    // TODO(nitesh): Fix this using std::move


    // TODO(nitesh): Add functionality for unload a mesh and clearing all the references
}

void SimpleRenderer::draw()
{
    glUseProgram(program.programid);
    for(std::pair<VertexArray, Mesh> entry: vertexarrays)
    {
        VertexArray vertexarr = entry.first;
        Mesh mesh = entry.second;

        if(program.shaderinfo.model_mat)
            glUniformMatrix4fv(program.model_mat_location, 1, GL_FALSE, glm::value_ptr(mesh.model_mat));
        if(program.shaderinfo.view_mat)
            glUniformMatrix4fv(program.view_mat_location, 1, GL_FALSE, glm::value_ptr(view_matrix));
        if(program.shaderinfo.projection_mat)
            glUniformMatrix4fv(program.projection_mat_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mesh.texture.id);

        //vertexarr.bind_and_render();
        glBindVertexArray(vertexarr.id);
        glDrawElements(GL_TRIANGLES, vertexarr.renderbuffer.triangle_count * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}