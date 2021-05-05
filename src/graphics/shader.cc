#include <graphics/shader.hh>
#include <util/resource.hh>


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


ShaderProgram::ShaderProgram(std::string vertexshadersource, std::string fragmentshadersource, ShaderInfo _shaderinfo):shaderinfo(_shaderinfo)
{
    std::vector<std::pair<std::string, int>> shader_sources;
    shader_sources.push_back(std::make_pair(vertexshadersource, GL_VERTEX_SHADER));
    shader_sources.push_back(std::make_pair(fragmentshadersource, GL_FRAGMENT_SHADER));

    load_program_from_source_list(shader_sources);

    // Setting up all the uniforms and other values
    load_all_uniform_variables(_shaderinfo);
}

ShaderProgram::ShaderProgram(std::vector<std::pair<std::string, int>> shader_source, ShaderInfo _shaderinfo):shaderinfo(_shaderinfo)
{
    load_program_from_source_list(shader_source);

    // Setting up all the uniforms and other values
    load_all_uniform_variables(_shaderinfo);
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

void ShaderProgram::load_all_uniform_variables(ShaderInfo _shaderinfo)
{
    if(programid == 0) return;

    shaderinfo = _shaderinfo;

    if(shaderinfo.model_mat)
    {
        model_mat_location = glGetUniformLocation(programid, "model");
        if(model_mat_location == -1)
        {
            printf("Unable to laod model uniform location");
        }
    }
    if(shaderinfo.view_mat)
    {
        view_mat_location = glGetUniformLocation(programid, "view");
        if(view_mat_location == -1)
        {
            printf("Unable to laod view uniform location");
        }
    }
    if(shaderinfo.projection_mat)
    {
        projection_mat_location = glGetUniformLocation(programid, "projection");
        if(projection_mat_location == -1)
        {
            printf("Unable to laod projection uniform location");
        }
    }
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