#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>

namespace Symphony
{
    std::map<Shader::DefaultShaderName, Shader*> Shader::defaultShaders;

    Shader::Shader(void)
    {
        _totalShaders = 0;
        _shaders[VERTEX_SHADER] = 0;
        _shaders[FRAGMENT_SHADER] = 0;
        _shaders[GEOMETRY_SHADER] = 0;
        
        //TO-DO: check if these should be necessary at this point
        //_attributeList.clear();
        //_uniformLocationList.clear();
    }

    Shader::~Shader(void)
    {
        //TO-DO: check if these should be necessary at this point
        //_attributeList.clear();
        //_uniformLocationList.clear();
    }

    void Shader::DeleteShaderProgram()
    {
        //TO-DO: Check if the shader object should be deleted along with its associated program
        glDeleteProgram(_program);
    }

    bool Shader::LoadFromString(GLenum type, const std::string& source)
    {
        GLuint shader = glCreateShader(type);

        const char * ptmp = source.c_str();
        glShaderSource(shader, 1, &ptmp, NULL);

        //check whether the shader loads fine
        GLint status;
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint infoLogLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar *infoLog = new GLchar[infoLogLength];
            glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
            std::cerr << "Compile log: " << infoLog << std::endl;
            delete[] infoLog;
            return false;
        }

        //TO-DO: Should this consider Geomtry Shaders as well?
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex shader " : "Fragment shader ") << "compiled" << std::endl;

        _shaders[_totalShaders++] = shader;

        return true;
    }


    bool Shader::CreateAndLinkProgram()
    {
        _program = glCreateProgram();
        if (_shaders[VERTEX_SHADER] != 0)
        {
            glAttachShader(_program, _shaders[VERTEX_SHADER]);
        }
        if (_shaders[FRAGMENT_SHADER] != 0)
        {
            glAttachShader(_program, _shaders[FRAGMENT_SHADER]);
        }
        if (_shaders[GEOMETRY_SHADER] != 0)
        {
            glAttachShader(_program, _shaders[GEOMETRY_SHADER]);
        }

        //link and check whether the program links fine
        GLint status;
        glLinkProgram(_program);
        glGetProgramiv(_program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint infoLogLength;

            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar *infoLog = new GLchar[infoLogLength];
            glGetProgramInfoLog(_program, infoLogLength, NULL, infoLog);
            std::cerr << "Link log: " << infoLog << std::endl;
            delete[] infoLog;
            return false;
        }

        std::cout << "Linking of the shaders was successful" << std::endl;

        glDeleteShader(_shaders[VERTEX_SHADER]);
        glDeleteShader(_shaders[FRAGMENT_SHADER]);
        glDeleteShader(_shaders[GEOMETRY_SHADER]);

        return true;
    }

    void Shader::Use()
    {
        glUseProgram(_program);
    }

    void Shader::Release()
    {
        glUseProgram(0);
    }

    void Shader::AddAttribute(const std::string& attribute)
    {
        _attributeList[attribute] = glGetAttribLocation(_program, attribute.c_str());
    }

    //An indexer that returns the location of the attribute
    GLuint Shader::operator[](const std::string& attribute)
    {
        return _attributeList[attribute];
    }

    void Shader::AddUniform(const std::string& uniform)
    {
        _uniformLocationList[uniform] = glGetUniformLocation(_program, uniform.c_str());
    }

    GLuint Shader::operator()(const std::string& uniform)
    {
        return _uniformLocationList[uniform];
    }

    bool Shader::LoadFromFile(GLenum whichShader, const std::string& filename)
    {
        //TO-DO: Should this consider Geomtry Shaders as well?
        std::cout << "Loading " << (whichShader == GL_VERTEX_SHADER ? "vertex shader (" : "fragment shader (") << filename << ")" << std::endl;

        std::ifstream fp;
        fp.open(filename.c_str(), std::ios_base::in);

        if (fp)
        {
            std::string line, buffer;
            while (std::getline(fp, line))
            {
                buffer.append(line);
                buffer.append("\r\n");
            }
            //copy to source
            return LoadFromString(whichShader, buffer);
        }
        else {
            std::cerr << "Error loading shader: " << filename << std::endl;
            return false;
        }
    }

    Shader* Shader::CreateNewShader(std::string vertexShaderFilename, std::string fragmentShaderFilename,
                                    std::vector<std::string> attributes, std::vector<std::string> uniforms)
    {
        Shader* newShader = new Shader();

        std::cout << std::endl << std::endl;

        //GL_CHECK_ERRORS

        //load the shader
        if (!newShader->LoadFromFile(GL_VERTEX_SHADER, vertexShaderFilename))
            return nullptr;

        if (!newShader->LoadFromFile(GL_FRAGMENT_SHADER, fragmentShaderFilename))
            return nullptr;

        //compile and link shader
        if (!newShader->CreateAndLinkProgram())
            return nullptr;

        newShader->Use();

        //Add attributes
        for (unsigned int i = 0; i < attributes.size(); ++i)
        {
            newShader->AddAttribute(attributes[i]);
        }

        //Add uniforms
        for (unsigned int i = 0; i < uniforms.size(); ++i)
        {
            newShader->AddUniform(uniforms[i]);
        }

        newShader->Release();

        //GL_CHECK_ERRORS

        return newShader;
    }

}