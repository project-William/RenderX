#pragma once
#include "..//..//..//Common.h"

namespace renderx::graphics
{
	enum class ShaderDataType
	{
		NONE = 0, FLOAT, FLOAT2, FLOAT3, FLOAT4
	};

	static size_t GetShaderDataTypeSize(ShaderDataType type)
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

	static size_t GetComponentCount(ShaderDataType type)
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
		default:break;
		}
	}

	struct BufferElement
	{
		BufferElement(ShaderDataType type, const std::string& name)
			:m_Type(type), m_Name(name), m_Size(GetShaderDataTypeSize(type)),
			m_Count(GetComponentCount(type))
		{ }

		size_t GetElementCount()const { return m_Count; }
		size_t GetElementSize()const { return m_Size; }

	private:

		std::string m_Name;
		ShaderDataType m_Type;
		size_t m_Size;
		size_t m_Count;

	};

	class REN_API BufferLayout
	{
	private:
		std::vector<BufferElement> m_Elements;
		size_t m_Stride;

	public:
		BufferLayout() :m_Stride(0) {};
		~BufferLayout();
		BufferLayout(const std::initializer_list<BufferElement> elements);

		const std::vector<BufferElement>& GetBufferElements()const { return m_Elements; }
		size_t GetStride()const { return m_Stride; }
	};
}