#pragma once
#include "..//..//Core.h"

namespace renderx {	
	namespace events {

		enum class REN_API EventType
		{
			NONE = 0,
			WindowResized,
			WindowClosed
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


	}
}