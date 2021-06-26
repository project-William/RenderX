#include "pch.h"

namespace renderx::Core
{
	

	enum class ShaderDataType
	{
		FLOAT2,FlOAT3,FLOAT4
	};

	static size_t GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT2:
			return 2;
			break;
		case ShaderDataType::FlOAT3:
			return 3;
			break;
		case ShaderDataType::FLOAT4:
			return 4;
			break;
		default:
			break;
		}
	}


	struct Element
	{
		Element(ShaderDataType type, const std::string& name)
			:m_Type(type),m_Name(name)
		{ }
		
		size_t GetStride() { return 36; }
		size_t GetSize() { return GetShaderDataTypeSize(m_Type); }
	private:
		ShaderDataType m_Type;
		std::string m_Name;
	};


	class VertexArray
	{
	private:
		uint32_t m_ArrayID;
		std::vector<Element> m_Element;

	public:
		VertexArray();
		~VertexArray();


		void BindVertexArray();
		void UnbindVertexArray();

		void SubmitBufferLayout(std::initializer_list<Element> eleList);
		std::vector<Element>& GetBufferElement() { return m_Element; }


		uint32_t GetVertexArrayID()const { return m_ArrayID; }

	};
}