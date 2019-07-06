#pragma once
#include "..//Layer.h"
#include "..//shader/ShaderProgram.h"
#include "..//VAOVBOEBO/VertexArray.h"

namespace renderx {
	namespace  graphics {

		class REN_API Render
		{
		private:
			ShaderProgram* m_ShaderProgram;
			VertexArray* m_VertexArray;
		public:
			Render();
			Render(const std::string& vfile,const std::string& ffile);
			~Render();

			void SetUp();

			Render& operator=(const Render& other) = delete;
			Render(const Render& other) = delete;

			inline VertexArray& GetVertexArray()const { return *m_VertexArray; }
			inline ShaderProgram& GetShaderProgram()const { return *m_ShaderProgram; }

		};

	}
}