#pragma once
#include "..//..//Core.h"

namespace renderx {	
	namespace events {

		enum class EventType
		{
			NONE = 0,
			WindowResized,
			MouseMovement,
			WindowClosed,
			ScrollMovement,
			KeyTyped
		};

		class REN_API Event
		{
		public:
		
			Event(){}
			virtual ~Event(){}

			virtual EventType GetEventType()const = 0;
			virtual const char* GetEventName()const = 0;
			virtual const std::string To_String()const { return GetEventName(); }

		};

#define EVENT_CLASS_TYPE(type) virtual EventType GetEventType() const override { return EventType::##type; }

#define EVENT_NAME_TYPE(type) virtual const char* GetEventName() const override { return #type; }

	}
}