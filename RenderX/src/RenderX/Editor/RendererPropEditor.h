#pragma once

namespace renderx::ui
{
	class RendererPropEditor
	{
	public:
		static std::shared_ptr<RendererPropEditor>& Get();

		~RendererPropEditor();

		void RunPropEditor();
		void UpdateTexture();
		void UpdateTransformation(const std::string& name);
		void ColorPicker(const std::string& name);
	private:
		static std::shared_ptr<RendererPropEditor> s_Instance;
		RendererPropEditor();
	};
}