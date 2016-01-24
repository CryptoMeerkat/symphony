#pragma once

#include <map>
#include <string>
#include <GLEW/GL/glew.h>

using namespace std;

namespace Symphony
{
    class Shader
    {
    public:
        enum DefaultShaderName { UNLIT_COLOR, UNLIT_TEXTURE, MIRROR_WATER, DIFFUSE, BUMPED_DIFFUSE, SKYBOX, BLUR_SHADER };

        Shader();
        ~Shader();

        bool LoadFromString(GLenum whichShader, const string& source);
        bool LoadFromFile(GLenum whichShader, const string& filename);
        bool CreateAndLinkProgram();
        void Use();
        void Release();
        void AddAttribute(const string& attribute);
        void AddUniform(const string& uniform);

        //An indexer that returns the location of the attribute/uniform
        GLuint operator[](const string& attribute);
        GLuint operator()(const string& uniform);

        GLuint ProgramID() { return _program; }

        void DeleteShaderProgram();

        bool HasUniform(string uniform)
        {
            if (_uniformLocationList.find(uniform) == _uniformLocationList.end())
                return false;

            return true;
        }

        static void AddShader(DefaultShaderName typeOfShader, Shader* shaderObj)
        {
            defaultShaders[typeOfShader] = shaderObj;
        }

        static Shader* GetShader(DefaultShaderName typeOfShader)
        {
            if (defaultShaders.find(typeOfShader) == defaultShaders.end())
                return nullptr;

            return defaultShaders[typeOfShader];
        }

    protected:
        enum Type { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
        GLuint _program;
        int _totalShaders;
        GLuint _shaders[3]; //0: vertex shader, 1: fragment shader, 2: geometry shader
        map<string, GLuint> _attributeList;
        map<string, GLuint> _uniformLocationList;

        static map<DefaultShaderName, Shader*> defaultShaders;
    };
}