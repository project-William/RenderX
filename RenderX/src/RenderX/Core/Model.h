#pragma once
#include "pch.h"
#include "Mesh.h"

namespace renderx::Core
{
    class Model
    {
    public:
        // model data 
        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh>    meshes;
        std::string directory;
        bool gammaCorrection;
        BoundingBox m_AABB;

        std::string m_MeshDir;
         
        // constructor, expects a filepath to a 3D model.
        Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
        {
            m_MeshDir = path;
            loadModel(path);
        }

        // draws the model, and thus all its meshes
        void Draw();

    private:
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(std::string const& path);

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode* node, const aiScene* scene);

        Mesh processMesh(aiMesh* mesh, const aiScene* scene);


        unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
        
        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        
        void CalculateAABB(int index = 0);

    };


    
}