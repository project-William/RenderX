#include "pch.h"
#include "Hdr.h"
#include "../Base/Window.h"

namespace renderx::Core
{
    std::shared_ptr<Hdr> Hdr::s_Instance;
    
    std::shared_ptr<Hdr> Hdr::Get()
    {
        if (!s_Instance)
        {
            s_Instance = std::shared_ptr<Hdr>(new Hdr());
        }
        return s_Instance;
    }



    Hdr::Hdr()
        :m_Exposure(1.25f)
	{
        m_Shader = std::shared_ptr<Shader>(new Shader("shaderSource/hdr.vert", "shaderSource/hdr.frag"));
        glGenFramebuffers(1, &m_HdrFBO);
        // create floating point color buffer
        glGenTextures(1, &m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // create depth buffer (renderbuffer)
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height);
        // attach buffers
        glBindFramebuffer(GL_FRAMEBUFFER, m_HdrFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_Shader->UseShaderProgram();
        m_Shader->SetInt("hdrBuffer", 0);
	}


	Hdr::~Hdr()
	{
	}

    unsigned int Hdr::GetColorAttachment()
    {
        return m_ColorAttachment;
    }

	void Hdr::UpdateColorAttachment(int x,int y)
	{
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, x, y, 0, GL_RGBA, GL_FLOAT, NULL);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // create depth buffer (renderbuffer)
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, x, y);
        // attach buffers
        glBindFramebuffer(GL_FRAMEBUFFER, m_HdrFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}