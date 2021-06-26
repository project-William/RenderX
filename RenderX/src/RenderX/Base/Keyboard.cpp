#include "pch.h"
#include "Keyboard.h"

namespace renderx::base
{
	std::shared_ptr<Keyboard> Keyboard::s_Instance;

	std::shared_ptr<Keyboard> Keyboard::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<Keyboard>(new Keyboard());
			return s_Instance;
		}
		return s_Instance;
	}

	Keyboard::Keyboard()
		:m_Keys(nullptr),m_IsKeyPressed(false)
	{
		int32_t keyNums = Keys::RX_KEY_LAST;
		m_Keys = new std::vector<bool>(keyNums);
	}

	void Keyboard::OnEvent(KeyPressedEvent& event)
	{
		(*m_Keys)[event.GetKeyCode()] = true;
		m_IsKeyPressed = true;
	}

	void Keyboard::OnEvent(KeyReleasedEvent& event)
	{
		(*m_Keys)[event.GetKeyCode()] = false;
		m_IsKeyPressed = false;

	}
}