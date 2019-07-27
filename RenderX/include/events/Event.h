#pragma once
#include "..//..//Core.h"

namespace renderx {	
	namespace events {

		enum class EventType
		{
			NONE = 0,
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
			NONE = 0,
			RX_EVENT_CATEGORY_INPUT = VALUE(0),
			RX_EVENT_CATEGORY_MOUSE = VALUE(1),
			RX_EVENT_CATEGORY_MOUSE_BUTTON = VALUE(2),
			RX_EVENT_CATEGORY_KEYBOARD = VALUE(3),
			RX_EVENT_CATEGORY_WINDOW = VALUE(4),
			RX_EVENT_CATEGORY_GUI = VALUE(5)
		};

		class REN_API Event
		{
		public:
			friend class EventDispatcher;
			Event(){}
			virtual ~Event(){}
			static EventType GetStaticEventType() { return EventType::NONE; }
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

					m_Event.m_Handled = efunc(*(T*)& m_Event);
					return true;
				}

				return false;
			}



		};







	}
}