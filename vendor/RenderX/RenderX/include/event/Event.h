#pragma once
#include "..//..//Common.h"

namespace renderx::events {

	enum class REN_API EventType
	{
		RX_NONE_EVENT = 0,
		RX_WINDOW_RESIZE,
		RX_WINDOW_CLOSE,
		RX_WINDOW_MOVE,
		RX_MOUSE_MOVE,
		RX_MOUSE_BUTTON,
		RX_MOUSE_PRESS,
		RX_MOUSE_RELEASE,
		RX_MOUSE_SCROLL,
		RX_KEYBOARD,
		RX_KEY_PRESS,
		RX_KEY_RELEASE,
		RX_KEY_TYPE
	};


	enum REN_API EventCategory
	{
		RX_NONE_CG = 0,
		RX_EVENT_CATEGORY_INPUT = TWO_SQUARE(0),
		RX_EVENT_CATEGORY_MOUSE = TWO_SQUARE(1),
		RX_EVENT_CATEGORY_MOUSE_BUTTON = TWO_SQUARE(2),
		RX_EVENT_CATEGORY_KEYBOARD = TWO_SQUARE(3),
		RX_EVENT_CATEGORY_WINDOW = TWO_SQUARE(4),
		RX_EVENT_CATEGORY_GUI = TWO_SQUARE(5)
	};


	class REN_API Event
	{
	public:
		friend class EventDispatcher;
		Event() {}
		virtual ~Event() {}
		static EventType GetStaticEventType() { return EventType::RX_NONE_EVENT; }
		virtual EventType GetEventType()const = 0;
		virtual const char* GetEventName()const = 0;
		virtual int GetCategoryFlags()const = 0;

		virtual const std::string To_String()const { return GetEventName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:

		bool m_Handled = false;

	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticEventType() {return EventType::##type;}\
		virtual EventType GetEventType() const override { return GetStaticEventType(); }

#define EVENT_NAME_TYPE(type) virtual const char* GetEventName() const override { return #type; }

#define EVENT_CATEGORY_TYPE(category) virtual int GetCategoryFlags()const override { return category; }

	class REN_API EventDispatcher
	{
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{

		}


		//dispatcher the event to the appropriate listener
		template<typename T>
		bool Dispatch(std::function<bool(T&)> efunc)
		{
			if (!m_Event.m_Handled && m_Event.GetEventType() == T::GetStaticEventType())
			{

				m_Event.m_Handled = efunc(*(T*)&m_Event);
				return true;
			}

			return false;
		}



	};
}