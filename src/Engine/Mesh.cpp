#include "Mesh.h"

namespace Symphony
{
    Mesh::Mesh()
    {
        numberOfVertices = 0;
        numberOfIndices = 0;

        vertices = nullptr;
        indices = nullptr;
        colours = nullptr;
        normals = nullptr;

        typeOfPrimitive = GL_TRIANGLES;

        for (unsigned short i = 0; i < MAX_BUFFER; ++i)
        {
            vboID[i] = 0;
        }
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(MAX_BUFFER, vboID);

        delete[] vertices;
        delete[] indices;
        delete[] colours;
        delete[] normals;

        //`TextureData` will take charge of releasing anything related to textures
    }

    Mesh* Mesh::Triangle()
    {
        Mesh* triangle = new Mesh();

        triangle->typeOfPrimitive = GL_TRIANGLES;

        triangle->numberOfVertices = 3;

        triangle->vertices = new glm::vec3[triangle->numberOfVertices];
        triangle->vertices[0] = glm::vec3(0, 1, 0);
        triangle->vertices[1] = glm::vec3(1, -1, 0);
        triangle->vertices[2] = glm::vec3(-1, -1, 0);

        triangle->colours = new glm::vec4[triangle->numberOfVertices];
        triangle->colours[0] = glm::vec4(1, 0, 0, 1);
        triangle->colours[1] = glm::vec4(0, 1, 0, 1);
        triangle->colours[2] = glm::vec4(0, 0, 1, 1);

        triangle->numberOfIndices = 3;
        triangle->indices = new GLuint[triangle->numberOfIndices];
        triangle->indices[0] = 0;
        triangle->indices[1] = 1;
        triangle->indices[2] = 2;

        triangle->BufferData();

        return triangle;
    }

    void Mesh::BufferData()
    {
        //setup triangle vao and vbo stuff
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        glGenBuffers(1, &vboID[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vboID[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_BUFFER);

        GL_CHECK_ERRORS

        if (colours)
        {
            glGenBuffers(1, &vboID[COLOUR_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[COLOUR_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec4), colours, GL_STATIC_DRAW);

            glEnableVertexAttribArray(COLOUR_BUFFER);
            glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);

            GL_CHECK_ERRORS
        }

        if (indices)
        {
            glGenBuffers(1, &vboID[INDEX_BUFFER]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[INDEX_BUFFER]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

            GL_CHECK_ERRORS
        }

        if (normals)
        {
            glGenBuffers(1, &vboID[NORMAL_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[NORMAL_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), normals, GL_STATIC_DRAW);

            glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(NORMAL_BUFFER);

            GL_CHECK_ERRORS
        }

        glBindVertexArray(0);
    }
}