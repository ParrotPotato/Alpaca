#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

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

enum ShaderUniformType
{
    none,
    matrix4x4,
    matrix3x3,
    float3,
    float2,
    float1,
    int3,
    int2,
    int1
};

struct ShaderUniformTuple
{
    std::string name;
    ShaderUniformType type;
};

struct ShaderUniformInfo
{
    std::vector<ShaderUniformTuple> tuples;
};



struct ShaderProgram
{
    ShaderProgram() = default;

    ShaderProgram(std::string vertexshadersource, std::string fragmentshadersource, ShaderUniformInfo _uniforminfo);
    ShaderProgram(std::vector<std::pair<std::string, int>> shadersourcelist, ShaderUniformInfo _uniforminfo);

    void load_program_from_source_list(std::vector<std::pair<std::string, int>> shadersourcelist);
    void load_all_uniform_variables();

    void delete_shader_program();

    struct ShaderUniformLocation
    {
        ShaderUniformType type;
        GLint location;
    };

    template <typename UniformData_t>
    void update_uniform_data(std::string uniform_name, UniformData_t data);


    ShaderUniformInfo uniforminfo;
    std::unordered_map<std::string, ShaderUniformLocation> locations;

    std::vector<Shader> shaders;
    GLuint programid = 0;

    // I think we should used a derived class for the following information for 
    // maintaining seperation of concerns but lets start with a in class implementation

    GLint model_mat_location;
    GLint view_mat_location;
    GLint projection_mat_location;
};

#endif