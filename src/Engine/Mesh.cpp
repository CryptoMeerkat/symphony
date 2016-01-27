#include "Mesh.h"

#include "Color.h"

namespace Symphony
{
    Mesh::Mesh()
    {
        numberOfVertices = 0;
        numberOfIndices = 0;

        vertices    = nullptr;
        indices     = nullptr;
        colours     = nullptr;
        normals     = nullptr;
        tangents    = nullptr;

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
        triangle->colours[0] = Color::White();
        triangle->colours[1] = Color::White();
        triangle->colours[2] = Color::White();
        
        triangle->numberOfIndices = 3;
        triangle->indices = new GLuint[triangle->numberOfIndices];
        triangle->indices[0] = 0;
        triangle->indices[1] = 1;
        triangle->indices[2] = 2;

        triangle->BufferData();

        return triangle;
    }

    Mesh* Mesh::Quad()
    {
        Mesh* quad = new Mesh();

        quad->typeOfPrimitive = GL_TRIANGLE_STRIP;

        quad->numberOfVertices = 4;
        quad->vertices = new glm::vec3[quad->numberOfVertices];
        quad->vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
        quad->vertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
        quad->vertices[2] = glm::vec3(1.0f, -1.0f, 0.0f);
        quad->vertices[3] = glm::vec3(1.0f, 1.0f, 0.0f);
        
        quad->colours = new glm::vec4[quad->numberOfVertices];
        quad->colours[0] = Color::White();
        quad->colours[1] = Color::White();
        quad->colours[2] = Color::White();
        quad->colours[3] = Color::White();

        quad->normals = new glm::vec3[quad->numberOfVertices];
        quad->normals[0] = glm::vec3(0, 0, 1);
        quad->normals[1] = glm::vec3(0, 0, 1);
        quad->normals[2] = glm::vec3(0, 0, 1);
        quad->normals[3] = glm::vec3(0, 0, 1);

        quad->tangents = new glm::vec3[quad->numberOfVertices];
        quad->tangents[0] = glm::vec3(1, 0, 0);
        quad->tangents[1] = glm::vec3(1, 0, 0);
        quad->tangents[2] = glm::vec3(1, 0, 0);
        quad->tangents[3] = glm::vec3(1, 0, 0);
        
        quad->numberOfIndices = 0;
        
        quad->BufferData();

        return quad;
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

        if (tangents)
        {
            glGenBuffers(1, &vboID[TANGENT_BUFFER]);
            glBindBuffer(GL_ARRAY_BUFFER, vboID[TANGENT_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(glm::vec3), tangents, GL_STATIC_DRAW); //texture.textureCoordinates

            glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(TANGENT_BUFFER);

            GL_CHECK_ERRORS
        }

        glBindVertexArray(0);
    }

    //TO-DO: Can this be const?
    void Mesh::Render()
    {
        glBindVertexArray(vaoID);

        if (vboID[INDEX_BUFFER])
        {
            glDrawElements(typeOfPrimitive, numberOfIndices, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(typeOfPrimitive, 0, numberOfVertices);
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Mesh::Colorize(glm::vec4 newColor)
    {
        if (colours)
        {
            for (size_t i = 0; i < numberOfVertices; ++i)
            {
                colours[i] = newColor;
            }
        }
        //TO-DO: Only BufferData() the colours
        BufferData();
    }

    void Mesh::Colorize(glm::vec4* newColors, int numberOfColors)
    {
        if (colours)
        {
            for (size_t i = 0; i < numberOfVertices; ++i)
            {
                colours[i] = newColors[i % numberOfColors];
            }
        }
        //TO-DO: Only BufferData() the colours
        BufferData();
    }
}