#pragma once

#include <map>
#include <GLEW/GL/glew.h>
#include <vector>

namespace Symphony
{
    class Shader
    {
    public:
        enum DefaultShaderName { UNLIT_COLOR }; // , UNLIT_TEXTURE, MIRROR_WATER, DIFFUSE, BUMPED_DIFFUSE, SKYBOX, BLUR_SHADER };

        Shader();
        ~Shader();
        
        void Use();
        void Release();
        bool CreateAndLinkProgram();
        void AddUniform(const std::string& uniform);
        void AddAttribute(const std::string& attribute);

        //An indexer that returns the location of the attribute/uniform
        GLuint operator[](const std::string& attribute);
        GLuint operator()(const std::string& uniform);

        GLuint ProgramID() { return _program; }

        void DeleteShaderProgram();

        bool HasUniform(std::string uniform)
        {
            if (_uniformLocationList.find(uniform) == _uniformLocationList.end())
                return false;

            return true;
        }

        static Shader* CreateNewShader(std::string vertexShaderFilename, std::string fragmentShaderFilename,
                                       std::vector<std::string> attributes, std::vector<std::string> uniforms);

        static void AddDefaultShader(DefaultShaderName typeOfShader, Shader* shaderObj)
        {
            defaultShaders[typeOfShader] = shaderObj;
        }

        static Shader* GetDefaultShader(DefaultShaderName typeOfShader)
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
        std::map<std::string, GLuint> _attributeList;
        std::map<std::string, GLuint> _uniformLocationList;

        bool LoadFromString(GLenum whichShader, const std::string& source);
        bool LoadFromFile(GLenum whichShader, const std::string& filename);

        static std::map<DefaultShaderName, Shader*> defaultShaders;
    };
}