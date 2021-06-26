#pragma once
#include "pch.h"
#include "../Utils/FileDialogs.h"


namespace renderx::ui
{
	class EnvironmentEditor
	{
	public:
		static std::shared_ptr<EnvironmentEditor>& Get();

		~EnvironmentEditor();

		void RunEnvironmentEditor();

	private:
		EnvironmentEditor();
		static std::shared_ptr<EnvironmentEditor> s_Instance;

				
	};
}