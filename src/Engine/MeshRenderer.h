#pragma once

#include "Mesh.h"
#include "Shader.h"

namespace Symphony
{
    struct MeshRenderer
    {
        Mesh* mesh;
        Shader* shader;
        
        MeshRenderer()
        {
            mesh = nullptr;
            shader = nullptr;
        }

        MeshRenderer(Mesh* mesh, Shader* shader)
        {
            this->mesh = mesh;
            this->shader = shader;
        }

        ~MeshRenderer()
        {
            //TO-DO: Determine who should delete the shaders, especially user-defined ones
            ////delete shader;
            delete mesh;
        }

        void ApplyValuesToShader(Shader* shader)
        {
            //TO-DO: Check why these need to be in this order when using the Unlit Shader
            if (shader->HasUniform("bumpTex"))
            {
                glUniform1i((*shader)("bumpTex"), 1);
            }

            //TO-DO: should we check if a texture exists for this object?
            if (shader->HasUniform("textureID"))
            {
                glUniform1i((*shader)("textureID"), 0);
            }
        }

        inline bool OkToRender() const
        {
            /*cout << "Mesh? " << std::boolalpha << (mesh != nullptr) << endl;
            cout << "Shader? " << std::boolalpha << (shader != nullptr) << endl;*/

            return mesh != nullptr && shader != nullptr;
        }
        
        inline void Render()
        {
            if (OkToRender())
                mesh->Render();
        }
    };
}