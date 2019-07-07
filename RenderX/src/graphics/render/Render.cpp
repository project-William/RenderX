#include "graphics/render/Render.h"

namespace renderx {
	namespace graphics {

		Render::Render()
			:m_VArray(nullptr)
		{
			m_VArray = new VertexArray(sizeof(vertices), vertices);
			m_VArray->AddBuffer(12, 0);
		}

		Render::~Render()
		{
			delete m_VArray;
		}


		void Render::Build()
		{
			
			std::string vs_source = utils::FileUtils::read_shader("shader/vertex.vert");
			const char* vs_src = vs_source.c_str();
			std::string fs_source = utils::FileUtils::read_shader("shader/fragment.frag");
			const char* fs_src = fs_source.c_str();

			std::cout << vs_src << std::endl;
			std::cout << fs_src << std::endl;
			GLuint vs = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vs, 1, &vs_src, NULL);
			glCompileShader(vs);

			GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fs, 1, &fs_src, NULL);
			glCompileShader(fs);

			m_ShaderProgram = glCreateProgram();
			glAttachShader(m_ShaderProgram, vs);
			glAttachShader(m_ShaderProgram, fs);
			glLinkProgram(m_ShaderProgram);

			
		}

		void Render::RenderAttrib()
		{

		}


		void Render::use()
		{
			glUseProgram(m_ShaderProgram);
		}

		void Render::Draw()
		{
			m_VArray->BindVertexArray();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	
	}
}