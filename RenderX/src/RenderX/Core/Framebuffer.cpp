#include "pch.h"
#include "Framebuffer.h"
#include "../Base/Window.h"
#include "Texture.h"


namespace renderx::Core
{



    void FrameBuffer::SetupFramebuffer()
    {
        
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Width, m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

    }

   

    void FrameBuffer::CreateTextureAttachment()
    {
        
        if (m_ColorAttachment)
        {
            //glDeleteFramebuffers(1, &m_FBO);
            //glDeleteRenderbuffers(1, &m_RBO);
            glDeleteTextures(1, &m_ColorAttachment);
        }
        //glfwGetFramebufferSize(base::Window::Get()->GetNativeWindow(), &width, &height);
        //glViewport(0, 0, width, height);


        //glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        //
        //TextureLoader::CreateColorAttachment(m_Width, m_Height, m_ColorAttachment);
        //std::cout << "this is texture:" << m_Width << std::endl;
        glGenTextures(1, &m_ColorAttachment);
        
        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        
        // Give an empty image to OpenGL ( the last "0" )
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        // Poor filtering. Needed !
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // Set "renderedTexture" as our colour attachement #0
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        //glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Width, m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void FrameBuffer::CreateRenderbuffer()
    {
        
    }

    

    void FrameBuffer::UpdateRenderStorage()
    {
        glDeleteRenderbuffers(1, &m_RBO);
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Width,m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
    }

    void FrameBuffer::BindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    }

    void FrameBuffer::UnbindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::BindRenderbuffer()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    }

    void FrameBuffer::UnbindRenderbuffer()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
    void FrameBuffer::Resize(unsigned int width, unsigned int height)
    {
        m_Width = width;
        m_Height = height;
        CreateTextureAttachment();
    }

    void FrameBuffer::DeleteColorAttachment()
    {
        glDeleteTextures(1, &m_ColorAttachment);
    }




















    std::shared_ptr<Framebuffer> Framebuffer::s_Instance;
    
    Framebuffer::Framebuffer()
    {

    }

    std::shared_ptr<Framebuffer>& Framebuffer::Get()
    {
        if (!s_Instance)
        {
            s_Instance = std::shared_ptr<Framebuffer>(new Framebuffer());
        }

        return s_Instance;
    }

    Framebuffer::~Framebuffer()
    {
        
    }

    void Framebuffer::BindFramebuffer(const std::string& name)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBOMap.find(name)->second.m_FBO);
    }

    void Framebuffer::UnBindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void Framebuffer::CreateFramebuffer(const std::string& name)
    {

    }
    //void FrameBuffer::SetFramebufferTexture2D(int idx, unsigned int texture, TextureType type, int mip)
    //{
    //    switch (type)
    //    {
    //    case TEXTURE2D:
    //        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D+ idx, texture, mip);
    //        break;
    //    case TEXTURE_CUBE:
    //        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + idx, texture, mip);
    //        break;
    //    default:
    //        break;
    //    }
    //
    //}
}