#pragma once
#include "..//..//..//Common.h"
#include "Renderer.h"
#include "..//Shader.h"
#include "Mesh.h"

namespace renderx::graphics
{

	class REN_API Model
	{
	public:
		std::vector<TextureInfo> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		bool gammaCorrection;

		Model(const char* path)
		{
			loadModel(path);
		}
		void Draw(std::shared_ptr<Shader> shader);
	private:
		std::vector<Mesh> meshes;
		std::string directory;
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<TextureInfo> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	};
}