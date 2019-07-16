#pragma once
#include "..//..//Core.h"

namespace renderx {
	namespace graphics {

		class REN_API FrameBuffer
		{
		private:
			GLuint m_FrameBufferID;
		public:
			FrameBuffer();
			~FrameBuffer();

			void BindFrameBuffer();
			void UnbindFrameBuffer();
		private:

		};

	}
}