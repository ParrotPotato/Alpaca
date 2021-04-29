#include <graphics/vertexattrib.hh>
#include <graphics/mesh.hh>


RenderBuffer::RenderBuffer(Mesh mesh)
{
    // creating vertex buffer

    glGenBuffers(1, &vertexbuffer);

    std::vector<glm::vec3> posnormal;

    for(size_t i = 0 ; i < mesh.position.size() ; i++)
    {
        posnormal.push_back(mesh.position[i]);
        posnormal.push_back(mesh.normal[i]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, posnormal.size() * sizeof(glm::vec3), (void *) posnormal.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    posnormal.clear();

    // creating the index buffer

    triangle_count = mesh.indices.size() / 3;

    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(int), (void *) mesh.indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



VertexArray::VertexArray(RenderBuffer _renderbuffer):renderbuffer(_renderbuffer)
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, _renderbuffer.vertexbuffer);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void *) sizeof(glm::vec3));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderbuffer.indexbuffer);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::bind_and_render()
{
    glBindVertexArray(id);
    glDrawElements(GL_TRIANGLES, renderbuffer.triangle_count * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}