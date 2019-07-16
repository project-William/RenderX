#pragma once
#include "..//Buffer.h"

namespace renderx {
	namespace graphics {

		enum class ShaderDataType
		{
			NONE =0,FLOAT,FLOAT2, FLOAT3, FLOAT4
		};

		static GLuint GetShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::NONE:		return 0;
				break;
			case ShaderDataType::FLOAT:		return sizeof(float);
				break;
			case ShaderDataType::FLOAT2:	return 2 * sizeof(float);
				break;
			case ShaderDataType::FLOAT3:	return 3 * sizeof(float);
				break;
			case ShaderDataType::FLOAT4:	return 4 * sizeof(float);
				break;
			}
		}

		static GLuint GetComponentCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::NONE:		return 0;
				break;
			case ShaderDataType::FLOAT:		return 1;
				break;
			case ShaderDataType::FLOAT2:	return 2;
				break;
			case ShaderDataType::FLOAT3:	return 3;
				break;
			case ShaderDataType::FLOAT4:	return 4;
				break;
			}
		}

		struct BufferElement
		{	BufferElement() :Type(), Name(), Size(0), Count(0) {}
			BufferElement(ShaderDataType type, const std::string& name)
				:Type(type),Name(name),Size(GetShaderDataTypeSize(type)),
				Count(GetComponentCount(type))
			{

			}

			inline GLuint GetElementCount()const { return Count; }
			inline GLuint GetElementSize()const { return Size; }

		private:

			std::string Name;
			ShaderDataType Type;
			GLuint Size;
			GLuint Count;

		};

		class REN_API BufferLayout
		{
		private:
			std::vector<BufferElement> m_Elements;
			GLuint m_Stride;

		public:
			BufferLayout();
			~BufferLayout();
			BufferLayout(const std::initializer_list<BufferElement> elements);

			inline const std::vector<BufferElement>& GetBufferElements()const { return m_Elements; }
			inline GLuint GetStride()const { return m_Stride; }

			void GetStride();


		};
	}
}