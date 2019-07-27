#include "utils/Keyboard.h"

namespace renderx {
	namespace utils {

		Keyboard* Keyboard::ms_Keyboard = nullptr;
		
		Keyboard::Keyboard()
			:m_Keys(nullptr)
		{
			int keyNums = Keys::RX_KEY_LAST;
			m_Keys = new std::vector<bool>(keyNums);
		}
		
		Keyboard::~Keyboard()
		{
			delete m_Keys;
		}

		Keyboard* Keyboard::Create()
		{
			if (!ms_Keyboard)
			{
				ms_Keyboard = new Keyboard();
				return ms_Keyboard;
			}
			return ms_Keyboard;
		}

		void Keyboard::OnEvent(events::KeyPressedEvent& event)
		{
			(*m_Keys)[event.GetKeyCode()] = true;
		}

		void Keyboard::OnEvent(events::KeyReleasedEvent& event)
		{
			(*m_Keys)[event.GetKeyCode()] = false;
		}

	}
}
