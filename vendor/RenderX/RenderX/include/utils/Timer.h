#pragma once
#include "..//..//Common.h"

namespace renderx::utils
{
	class REN_API Timer
	{
	public:
		Timer();
		~Timer();
		void Stop();

		double GetMilliseconds() const { return m_Duration; }

	private:
		double m_Duration;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;

	};

}