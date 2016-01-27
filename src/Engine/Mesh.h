#pragma once

#include <GLEW/GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Symphony
{
    #define GL_CHECK_ERRORS  glUniform4uiv(0,0,0);

    enum MeshBuffer {
        VERTEX_BUFFER,      //layout(location = 0)
        COLOUR_BUFFER,      //layout(location = 1)
        TEXTURE_BUFFER,     //layout(location = 2)
        NORMAL_BUFFER,      //layout(location = 3)
        TANGENT_BUFFER,     //layout(location = 4)
        INDEX_BUFFER,       //layout(location = 5)
        MAX_BUFFER
    };

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        inline void BindVAO()
        {
            glBindVertexArray(vaoID);
        }

        inline void UnBindVAO()
        {
            glBindVertexArray(0);
        }

        void Render();

        void Colorize(glm::vec4 newColor);
        void Colorize(glm::vec4* newColors, int numberOfColors);

        static Mesh* Triangle();
        static Mesh* Quad();

    protected:
        GLuint  vaoID,
                vboID[MeshBuffer::MAX_BUFFER],
                typeOfPrimitive;

        GLuint  numberOfVertices, numberOfIndices;

        GLuint*       indices;
        glm::vec3*    normals;
        glm::vec3*    tangents;
        glm::vec3*    vertices;
        glm::vec4*    colours;

        void BufferData();
    };
}