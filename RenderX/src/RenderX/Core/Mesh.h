#pragma once
#include "pch.h"
#include "AABB.h"

namespace renderx::Core
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh {
    public:
        // mesh Data
        std::vector<Vertex>       m_Vertices;
        std::vector<unsigned int> m_Indices;
        std::vector<Texture>      m_Textures;
        unsigned int m_VAO;
        std::string path;
        BoundingBox m_AABB;
        int index;
        // constructor
        Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
        // render the mesh
        void Draw();

    private:
        // render data 
        unsigned int m_VBO, m_EBO;

        // initializes all the buffer objects/arrays
        void setupMesh();

    };


}