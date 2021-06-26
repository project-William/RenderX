#pragma once
#include "pch.h"
#include "Texture.h"

namespace renderx::Core
{

	struct FBORBO
	{
		uint32_t m_FBO;
		uint32_t m_RBO;
	};

	class Framebuffer
	{
	public:
		static std::shared_ptr<Framebuffer>& Get();

		std::unordered_map<std::string, FBORBO> GetFBOMap() { return m_FBOMap; }

		~Framebuffer();
		void BindFramebuffer(const std::string& name);
		void UnBindFramebuffer();

		void CreateFramebuffer(const std::string& name);
		

	private:
		Framebuffer();
		static std::shared_ptr<Framebuffer> s_Instance;
		std::unordered_map<std::string, FBORBO> m_FBOMap;
	};



	class FrameBuffer
	{
	public:
		FrameBuffer(int width, int height) { m_Width = width; m_Height = height; }
		~FrameBuffer() {}
		void SetupFramebuffer();
		void CreateTextureAttachment();
		void CreateRenderbuffer();

		void UpdataFramebuffer();

		void UpdateRenderStorage();
		void BindFramebuffer();
		void UnbindFramebuffer();
		void BindRenderbuffer();
		void UnbindRenderbuffer();
		void Resize(unsigned int width, unsigned int height);
		//static void SetFramebufferTexture2D(int idx,unsigned int texture, TextureType type, int mip);
		unsigned int GetColorAttachment() { return m_ColorAttachment; }
		unsigned int GetDepthAttachment() { return m_DepthAttachment; }

		unsigned int GetWidth() { return m_Width; }
		unsigned int GetHeight() { return m_Height; }

		void DeleteColorAttachment();
		unsigned int GetFBO() { return m_FBO; }
		unsigned int GetRBO() { return m_RBO; }
	private:
		unsigned int m_FBO;
		unsigned int m_RBO;
		unsigned int m_ColorAttachment;
		unsigned int m_DepthAttachment;


		unsigned int m_Width;
		unsigned int m_Height;
	};
}