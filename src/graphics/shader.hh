#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <unordered_map>

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

// structure used to pass information regarding unifroms and other 
// shader constants
struct ShaderInfo
{
    bool model_mat = false;
    bool view_mat = false;
    bool projection_mat = false;
};

struct ShaderProgram
{
    ShaderProgram() = default;

    ShaderProgram(std::string vertexshadersource, std::string fragmentshadersource, ShaderInfo _shaderinfo = ShaderInfo());
    ShaderProgram(std::vector<std::pair<std::string, int>> shadersourcelist, ShaderInfo _shaderinfo = ShaderInfo());

    void load_program_from_source_list(std::vector<std::pair<std::string, int>> shadersourcelist);
    void load_all_uniform_variables(ShaderInfo _shaderinfo);

    void delete_shader_program();

    ShaderInfo shaderinfo;
    std::vector<Shader> shaders;
    GLuint programid = 0;

    // I think we should used a derived class for the following information for 
    // maintaining seperation of concerns but lets start with a in class implementation

    GLint model_mat_location;
    GLint view_mat_location;
    GLint projection_mat_location;
};

#endif