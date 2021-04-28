#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>

#include <string>
#include <vector>

struct Shader
{
    Shader() = default;
    Shader(std::string shadersourcename, int file);
    bool compile(char * shadersource, int flag);

    void delete_shader();

    GLuint shaderid = 0;
    int shadertype = 0;
};


// We are not going to use glGetAttribLocation because we are targetting
// opengl 3.3.0 or higher

struct ShaderProgram
{
    ShaderProgram() = default;

    ShaderProgram(std::string vertexshadersource, std::string fragmentshadersource);
    ShaderProgram(std::vector<std::pair<std::string, int>> shadersourcelist);
    void load_program_from_source_list(std::vector<std::pair<std::string, int>> shadersourcelist);

    void delete_shader_program();

    std::vector<Shader> shaders;
    GLuint programid = 0;
};

#endif