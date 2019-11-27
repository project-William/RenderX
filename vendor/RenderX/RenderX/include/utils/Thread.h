#pragma once
#include "..//..//Common.h"

namespace renderx::utils
{
	class REN_API Thread
	{
	public:
		~Thread() {}
		Thread& operator=(const Thread&) = delete;
		Thread(const Thread&) = delete;

		static std::shared_ptr<Thread> Create();


	private:
		Thread() {}
		static std::shared_ptr<Thread> m_Instance;

	};

}