#include "..//..//include/events/Event.h"

namespace renderx {
	namespace events {
		Event::Event(Type& type) :m_Type(type), m_Handled(false)
		{}

		Event::~Event()
		{}

		std::string Event::TypeToString(Type& type)
		{
			switch (type)
			{
			case Type::KEY_PRESSED:
				return "KEY_PRESSED";
				break;
			case Type::KEY_RELEASED:
				return "KEY_RELEASED";
				break;
			case Type::MOUSE_PRESSED:
				return "MOUSE_PRESSED";
				break;
			case Type::MOUSE_CLICKED:
				return "MOUSE_CLICKED";
				break;
			case Type::MOUSE_MOVED:
				return "MOUSE_MOVED";
				break;
			}
		}
	}
}