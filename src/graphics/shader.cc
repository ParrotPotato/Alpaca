#include <graphics/shader.hh>
#include <util/resource.hh>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string shadersourcename, int flag)
{
    auto shadersource = load_file_content(shadersourcename);
    if(shadersource.first == -1)
    {
        shaderid = 0;
        return;
    }

    compile(shadersource.second, flag);
}

bool Shader::compile(char * shadersource, int flag)
{
    shaderid = glCreateShader(flag);
    shadertype = flag;

    GLint result = GL_FALSE;
    int infolength = 0;

    glShaderSource(shaderid, 1, &shadersource, NULL);
    glCompileShader(shaderid);

    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &infolength);


    if(infolength > 0)
    {

        std::vector<char> errormessage(infolength);
        glGetShaderInfoLog(shaderid, infolength, NULL, errormessage.data());

        // TODO(nitesh): Add proper error code display
        printf("error compiling : %s\n%s\n", shadersource, errormessage.data());

        glDeleteShader(shaderid);
        shaderid = 0;
        shadertype = 0;

        return false;
    }
    return true;
}

void Shader::delete_shader()
{
    glDeleteShader(shaderid);
    shaderid = 0;
    shadertype = 0;
}


ShaderProgram::ShaderProgram(std::string vertexshadersource, std::string fragmentshadersource, ShaderUniformInfo _uniforminfo): uniforminfo(_uniforminfo)
{
    std::vector<std::pair<std::string, int>> shader_sources;
    shader_sources.push_back(std::make_pair(vertexshadersource, GL_VERTEX_SHADER));
    shader_sources.push_back(std::make_pair(fragmentshadersource, GL_FRAGMENT_SHADER));

    load_program_from_source_list(shader_sources);
    load_all_uniform_variables();
}
ShaderProgram::ShaderProgram(std::vector<std::pair<std::string, int>> shader_source, ShaderUniformInfo _uniforminfo): uniforminfo(_uniforminfo)
{
    load_program_from_source_list(shader_source);
    load_all_uniform_variables();
}

void ShaderProgram::load_program_from_source_list(std::vector<std::pair<std::string, int>> shader_source)
{
    programid = glCreateProgram();
    for(std::pair<std::string, int> x : shader_source)
    {
        Shader shader(x.first, x.second);
        if(shader.shaderid == 0)
        {
            printf("error occured while creating shader for program\n");
            delete_shader_program();
            return;
        }
        shaders.push_back(shader);

        glAttachShader(programid, shader.shaderid);
    }

    glLinkProgram(programid);

    GLint islinked = 0;
    GLint infolength = 0;

    glGetProgramiv(programid, GL_LINK_STATUS, (int *)&islinked);
    if(islinked == GL_FALSE)
    {
        glGetProgramiv(programid, GL_INFO_LOG_LENGTH, &infolength);
        std::vector<char> infolog(infolength);
        glGetProgramInfoLog(programid, infolength, &infolength, infolog.data());

        printf("unable to link program\n%s", infolog.data());

        delete_shader_program();
    }

    for(auto shader : shaders)
    {
        glDetachShader(programid, shader.shaderid);
    }

    return;
}

void ShaderProgram::load_all_uniform_variables()
{
    if(programid == 0) return;

    for(auto uniformtuple : uniforminfo.tuples)
    {
        GLint location = glGetUniformLocation(programid, uniformtuple.name.c_str());
        locations[uniformtuple.name] = {uniformtuple.type, location};
    }
}

template <typename UniformData_t> void ShaderProgram::update_uniform_data(std::string uniform_name, UniformData_t data){}

template <> void ShaderProgram::update_uniform_data<glm::mat4>(std::string uniform_name, glm::mat4 data)
{
    ShaderUniformLocation location = locations[uniform_name];

    if(location.type == matrix4x4)
        glUniformMatrix4fv(location.location, 1, GL_FALSE, glm::value_ptr(data));
    else
        printf("Attempting loading %s : mat4 for type ShaderUniformType:(%d)\n",uniform_name.c_str(), location.type);
}

template <> void ShaderProgram::update_uniform_data<int>(std::string uniform_name, int data)
{
    ShaderUniformLocation location = locations[uniform_name];

    if(location.type == int1)
        glUniform1i(location.location, data);
    else
        printf("Attempting loading int for type ShaderUniformType:(%d)\n",location.type);
}

template <> void ShaderProgram::update_uniform_data<float>(std::string uniform_name, float data)
{
    ShaderUniformLocation location = locations[uniform_name];

    if(location.type == float1)
        glUniform1f(location.location, data);
    else
        printf("Attempting loading float for type ShaderUniformType:(%d)\n",location.type);
}

void ShaderProgram::delete_shader_program()
{
    glDeleteProgram(programid);
    for (auto shader : shaders)
    {
        shader.delete_shader();
    }

    shaders.clear();

    programid = 0;
    return;
}