#include "utils/Keyboard.h"

namespace renderx::utils
{
	std::shared_ptr<Keyboard> Keyboard::ms_Keyboard;

	Keyboard::Keyboard()
		:m_Keys(nullptr)
	{
		int32_t keyNums = Keys::RX_KEY_LAST;
		m_Keys = new std::vector<bool>(keyNums);
	}

	Keyboard::~Keyboard()
	{
		delete m_Keys;
	}

	std::shared_ptr<Keyboard> Keyboard::Create()
	{
		if (!ms_Keyboard)
		{
			ms_Keyboard = std::shared_ptr<Keyboard>(new Keyboard());
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