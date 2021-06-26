#include "pch.h"
#include "EnvironmentEditor.h"
#include "../Core/IBL.h"
#include "../Core/Hdr.h"
#include "../Core/Skybox.h"

namespace renderx::ui
{
	std::shared_ptr<EnvironmentEditor> EnvironmentEditor::s_Instance;

	std::shared_ptr<EnvironmentEditor>& EnvironmentEditor::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<EnvironmentEditor>(new EnvironmentEditor());
		}
		return s_Instance;
	}

	EnvironmentEditor::EnvironmentEditor()
	{
	}

	EnvironmentEditor::~EnvironmentEditor()
	{
	}

	void EnvironmentEditor::RunEnvironmentEditor()
	{
		if (ImGui::Begin("Environment"))
		{
            ImGuiIO& io = ImGui::GetIO();
            ImGui::TextWrapped("Cubemap");

            // Below we are displaying the font texture because it is the only texture we have access to inside the demo!
            // Remember that ImTextureID is just storage for whatever you want it to be. It is essentially a value that
            // will be passed to the rendering back-end via the ImDrawCmd structure.
            // If you use one of the default imgui_impl_XXXX.cpp rendering back-end, they all have comments at the top
            // of their respective source file to specify what they expect to be stored in ImTextureID, for example:
            // - The imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer
            // - The imgui_impl_opengl3.cpp renderer expect a GLuint OpenGL texture identifier, etc.
            // More:
            // - If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers
            //   to ImGui::Image(), and gather width/height through your own functions, etc.
            // - You can use ShowMetricsWindow() to inspect the draw data that are being passed to your renderer,
            //   it will help you debug issues if you are confused about it.
            // - Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
            // - Read https://github.com/ocornut/imgui/blob/master/docs/FAQ.md
            // - Read https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
            float my_tex_w = (float)io.Fonts->TexWidth;
            float my_tex_h = (float)io.Fonts->TexHeight;
            {
                ImVec2 panelSize = ImGui::GetContentRegionAvail();
                float width = panelSize.x-10;
                float height = width/2.0f;
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImVec2 uv_min = ImVec2(1.0f, 1.0f);                 // Top-left
                ImVec2 uv_max = ImVec2(0.0f, 0.0f);                 // Lower-right
                ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
                ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
                ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                ImGui::SetCursorPosX((panelSize.x-width)*0.5f);
                if (ImGui::ImageButton((ImTextureID)(Core::IBL::Get()->GetHDRCubeMap().first), {width,height}, uv_min, uv_max, 2, bg_col, tint_col))
                {
                    Core::IBL::Get()->SetupIBL(utils::FileDialogs::OpenFile("").c_str());
                    Core::IBL::Get()->m_FramebufferRef.CreateTextureAttachment();
                }
                //ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    float region_sz = 32.0f;
                    float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
                    float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
                    float zoom = 4.0f;
                    if (region_x < 0.0f) { region_x = 0.0f; }
                    else if (region_x > my_tex_w - region_sz) { region_x = my_tex_w - region_sz; }
                    if (region_y < 0.0f) { region_y = 0.0f; }
                    else if (region_y > my_tex_h - region_sz) { region_y = my_tex_h - region_sz; }
                    ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
                    ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
                    ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
                    ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
                    ImGui::Image((ImTextureID)Core::IBL::Get()->GetHDRCubeMap().first, ImVec2(region_sz * zoom, region_sz * zoom), uv1, uv0, tint_col, border_col);
                    ImGui::EndTooltip();
                }
            }

            ImGui::Checkbox("Use Cubemap", &Core::Skybox::Get()->IsUseSkyboxRef());
            ImGui::Checkbox("Use Irrdiance", &Core::Skybox::Get()->IsUseIrridianceRef());
            ImGui::SliderFloat("Exposure", &Core::Hdr::Get()->GetExposureRef(), 0.0f, 10.0f);
                        
            ImGui::End();
		}
	}
}