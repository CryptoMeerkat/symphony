#include "Shader.h"

#include <iostream>
#include <fstream>

namespace Symphony
{
    map<Shader::DefaultShaderName, Shader*> Shader::defaultShaders;

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
        glDeleteProgram(_program);
    }

    bool Shader::LoadFromString(GLenum type, const string& source)
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
            cerr << "Compile log: " << infoLog << endl;
            delete[] infoLog;
            return false;
        }

        //TO-DO: Should this consider Geomtry Shaders as well?
        cout << (type == GL_VERTEX_SHADER ? "Vertex shader " : "Fragment shader ") << "compiled" << endl;

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
            cerr << "Link log: " << infoLog << endl;
            delete[] infoLog;
            return false;
        }

        cout << "Linking of the shaders was successful" << endl;

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

    void Shader::AddAttribute(const string& attribute)
    {
        _attributeList[attribute] = glGetAttribLocation(_program, attribute.c_str());
    }

    //An indexer that returns the location of the attribute
    GLuint Shader::operator[](const string& attribute)
    {
        return _attributeList[attribute];
    }

    void Shader::AddUniform(const string& uniform)
    {
        _uniformLocationList[uniform] = glGetUniformLocation(_program, uniform.c_str());
    }

    GLuint Shader::operator()(const string& uniform)
    {
        return _uniformLocationList[uniform];
    }

    bool Shader::LoadFromFile(GLenum whichShader, const string& filename)
    {
        //TO-DO: Should this consider Geomtry Shaders as well?
        cout << "Loading " << (whichShader == GL_VERTEX_SHADER ? "vertex shader (" : "fragment shader (") << filename << ")" << endl;

        ifstream fp;
        fp.open(filename.c_str(), ios_base::in);

        if (fp)
        {
            string line, buffer;
            while (getline(fp, line))
            {
                buffer.append(line);
                buffer.append("\r\n");
            }
            //copy to source
            return LoadFromString(whichShader, buffer);
        }
        else {
            cerr << "Error loading shader: " << filename << endl;
            return false;
        }
    }



}