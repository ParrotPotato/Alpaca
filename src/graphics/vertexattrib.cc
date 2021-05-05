#include <graphics/vertexattrib.hh>
#include <graphics/mesh.hh>

#include <cstddef> // used for offsetof

RenderBuffer::RenderBuffer(Mesh mesh)
{
    // creating vertex buffer

    glGenBuffers(1, &vertexbuffer);

    RenderBufferArrayLayoutDesc layoutdesc;
    layoutdesc = {0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position)};
    layout.push_back(layoutdesc);
    layoutdesc = {1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal)};
    layout.push_back(layoutdesc);
    layoutdesc = {2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv)};


    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), (void *) mesh.vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

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

    for(auto desc : _renderbuffer.layout)
    {
        glEnableVertexAttribArray(desc.vertex_attrib_array);
        glVertexAttribPointer(desc.vertex_attrib_array, desc.count, desc.type, desc.normalised, desc.stride, desc.offset);
    }

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