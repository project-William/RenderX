#pragma once
#include "..//..//Core.h"
#include "RenderBuffer.h"
#include "texture/Texture.h"
#include "Window.h"
#include "..//entity/HDRCubemap.h"

namespace renderx {
	namespace graphics {

		enum class FBTexAttachType
		{
			COLOR_ATTACH_0 = 0,
			COLOR_ATTACH_1 ,
			COLOR_ATTACH_2 ,
			COLOR_ATTACH_3 ,
			COLOR_ATTACH_4 ,
		};

		static GLuint GetFBTexAttachType(FBTexAttachType type)
		{
			switch (type)
			{
			case FBTexAttachType::COLOR_ATTACH_0:	return GL_COLOR_ATTACHMENT0;
				break;
			case FBTexAttachType::COLOR_ATTACH_1:	return GL_COLOR_ATTACHMENT1;
				break;
			case FBTexAttachType::COLOR_ATTACH_2:	return GL_COLOR_ATTACHMENT2;
				break;
			case FBTexAttachType::COLOR_ATTACH_3:	return GL_COLOR_ATTACHMENT3;
				break;
			case FBTexAttachType::COLOR_ATTACH_4:	return GL_COLOR_ATTACHMENT4;
				break;
			}
		}



		class REN_API FrameBuffer
		{
		private:
			GLuint m_FrameBufferID;
			RenderBuffer* m_RenderBuffer;
			Texture *m_BaseTexture;
		public:
			FrameBuffer();
			FrameBuffer(const WinData& windata);
			~FrameBuffer();

			void BindFrameBuffer();
			void UnbindFrameBuffer();
			void UpdateFramebufferData(const WinData& windata, bool& flag);

			void UpdateRenderBuffer(const graphics::WinData& windata);

			inline GLuint& GetRendered(){ return m_BaseTexture->GetTexRef(); }
			inline const GLuint& GetFrameBufferID()const { return m_FrameBufferID; }
			void InitFramebuffer(const WinData& windata);
			
		private:
			void AttachTexture(const GLuint& texture, FBTexAttachType type);
			void CreateBaseTexture(const graphics::WinData& windata);

			bool CheckInit();
		};

	}
}