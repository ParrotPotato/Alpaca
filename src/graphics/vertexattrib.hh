#ifndef VERTEX_ATTRIB_HH
#define VERTEX_ATTRIB_HH

#include <graphics/mesh.hh>

#include <GL/glew.h>



struct RenderBuffer 
{
    GLuint vertexbuffer = 0;
    GLuint indexbuffer = 0;
    RenderBuffer(Mesh mesh);

    unsigned int triangle_count;
};

struct VertexArray
{
    GLuint id;
    RenderBuffer renderbuffer;
    unsigned int triangle_count;
    VertexArray(RenderBuffer _renderbuffer);

    void bind_and_render();
};

#endif