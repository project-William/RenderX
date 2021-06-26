#pragma once
#include "pch.h"

#define BIT(x) (1<<x)

namespace renderx::base
{

	enum class EventType
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


	enum EventCategory
	{
		RX_NONE_CG = 0,
		RX_EVENT_CATEGORY_INPUT = BIT(0),
		RX_EVENT_CATEGORY_MOUSE = BIT(1),
		RX_EVENT_CATEGORY_MOUSE_BUTTON = BIT(2),
		RX_EVENT_CATEGORY_KEYBOARD = BIT(3),
		RX_EVENT_CATEGORY_WINDOW = BIT(4),
		RX_EVENT_CATEGORY_GUI = BIT(5)
	};


	class Event
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

	class EventDispatcher
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