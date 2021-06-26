#include "pch.h"
#include "Bloom.h"
#include "../Base/Window.h"

namespace renderx::Core
{
    std::shared_ptr<Bloom> Bloom::s_Instance;

    std::shared_ptr<Bloom> Bloom::Get()
    {
        if (!s_Instance)
        {
            s_Instance = std::shared_ptr<Bloom>(new Bloom());
        }
        return s_Instance;
    }

	Bloom::Bloom()
	{
        m_BloomShader = std::shared_ptr<Shader>(new Shader("shaderSource/bloom.vert", "shaderSource/bloom.frag"));
        m_LightShader = std::shared_ptr<Shader>(new Shader("shaderSource/bloom.vert", "shaderSource/light_box.frag"));
        m_BlurShader = std::shared_ptr<Shader>(new Shader("shaderSource/blur.vert", "shaderSource/blur.frag"));
        m_BloomFinalShader = std::shared_ptr<Shader>(new Shader("shaderSource/test.vert", "shaderSource/test.frag"));

        // configure (floating point) framebuffers
        // ---------------------------------------
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        // create 2 floating point color buffers (1 for normal rendering, other for brightness threshold values)
        glGenTextures(2, m_ColorAttachment);
        for (unsigned int i = 0; i < 2; i++)
        {
            glBindTexture(GL_TEXTURE_2D, m_ColorAttachment[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            // attach texture to framebuffer
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachment[i], 0);
        }
        // create and attach depth buffer (renderbuffer)
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
        // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
        unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, attachments);
        // finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // ping-pong-framebuffer for blurring
        glGenFramebuffers(2, m_PingpongFBO);
        glGenTextures(2, m_PingpongColorbuffers);
        for (unsigned int i = 0; i < 2; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_PingpongFBO[i]);
            glBindTexture(GL_TEXTURE_2D, m_PingpongColorbuffers[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, base::Window::Get()->GetWinDataVal().m_Width, base::Window::Get()->GetWinDataVal().m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_PingpongColorbuffers[i], 0);
            // also check if framebuffers are complete (no need for depth buffer)
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
        }

        m_BloomShader->UseShaderProgram();
        m_BloomShader->SetInt("diffuseTexture", 0);
        m_BlurShader->UseShaderProgram();
        m_BlurShader->SetInt("image", 0);
        m_BloomFinalShader->UseShaderProgram();
        m_BloomFinalShader->SetInt("scene", 0);
        m_BloomFinalShader->SetInt("bloomBlur", 1);

	}

	Bloom::~Bloom()
	{

	}
}