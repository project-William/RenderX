#pragma once
#include "..//shader/Shader.h"
#include "..//VAOVBOEBO/VertexArray.h"
#include "..//Window.h"
namespace renderx {
	namespace graphics {

		struct REN_API RenderData
		{
			std::unique_ptr<Shader> m_Shader = nullptr;
			std::unique_ptr<VertexArray> m_VAO = nullptr;
			BufferLayout m_Layout;
		};

		struct REN_API Transformation
		{
			glm::vec3 movement;
			float perspective_radians = 45.0f;
			glm::vec3 position;
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			glm::vec4 color;
		};


		class REN_API RenderObject
		{
		public:
			RenderObject() {}
			virtual ~RenderObject() {}

			virtual void BindObject() const = 0;
			virtual void UnbindObject() const = 0;
			virtual void Draw(const WinData& windata) = 0;
			virtual void Position() = 0;
			virtual void Rotation() = 0;
			virtual void Scale() = 0;
			virtual void RenderProperties() = 0;

		};


	}
}