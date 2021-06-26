#include "pch.h"
#include "MaterialEditor.h"
#include "../Utils/FileDialogs.h"
#include "../Core/RenderScene.h"
#include "../Core/Texture.h"


namespace renderx::ui
{
    unsigned int MaterialEditor::m_DefaultTexture;

    


	MaterialEditor::MaterialEditor()
	{
        m_DefaultTexture = Core::TextureLoader::LoadTexture("resource/textures/default.png", true);
	}

	MaterialEditor::~MaterialEditor()
	{
	}

	void MaterialEditor::RunMatrialEditor(const std::string& rendererName)
	{
        //auto& rendererIter = Core::RenderScene::Get()->GetRenderersRef().find(rendererName);

        auto& rendererMaterial = Core::RenderScene::Get()->GetRenderersMaterialMapRef().find(rendererName);

        if (rendererMaterial != Core::RenderScene::Get()->GetRenderersMaterialMapRef().end())
        {
            //auto& renderer = rendererIter->second;
            if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
            {
                static bool a = true;
                static bool b = true;
                static bool c = true;
                static bool d = true;
                static bool e = true;
                static float l = 0;


                ImGui::PushID(0);
                ShowTexture(rendererMaterial->second,rendererMaterial->second.albedoMap, "Albedo", a);
                ImGui::Checkbox("Use Albedo", &a);
                ImGui::Separator();
                ImGui::PopID();

                ImGui::PushID(1);
                ShowTexture(rendererMaterial->second, rendererMaterial->second.normalMap, "Normal", a);
                ImGui::Checkbox("Use Normal", &b);
                ImGui::Separator();
                ImGui::PopID();

                ImGui::PushID(2);
                ShowTexture(rendererMaterial->second, rendererMaterial->second.metallicMap, "Metallic", a);
                ImGui::Checkbox("Use Metallic", &c);
                ImGui::Separator();
                ImGui::PopID();

                ImGui::PushID(3);
                ShowTexture(rendererMaterial->second, rendererMaterial->second.roughnessMap, "Roughness", a);
                ImGui::Checkbox("Use Roughness", &d);
                ImGui::Separator();
                ImGui::PopID();

                ImGui::PushID(4);
                ShowTexture(rendererMaterial->second, rendererMaterial->second.aoMap, "AO", a);
                ImGui::Checkbox("Use Ao", &e);
                ImGui::Separator();
                ImGui::PopID();


            }
        }


        

	}

	void MaterialEditor::ShowTexture(Core::Material& material, unsigned int texture,const std::string& name, bool& isBindTexture)
	{
        ImGuiIO& io = ImGui::GetIO();
        //ImGui::TextWrapped(name.c_str());

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
        //ImTextureID my_tex_id = io.Fonts->TexID;
        float my_tex_w = (float)io.Fonts->TexWidth;
        float my_tex_h = (float)io.Fonts->TexHeight;
        {
            ImVec2 panelSize = ImGui::GetContentRegionAvail();
            float width = panelSize.x/3;
            float height = width;
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
            ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
            ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            //ImGui::SetCursorPosX((panelSize.x - width) * 0.5f);

            //ImGui::Image((void*)(renderer->GetMaterialRef()->GetAlbedoMap()), { 250,250 });
            if (ImGui::ImageButton((ImTextureID)(texture), { width,height }, uv_min, uv_max, 2, bg_col, tint_col))
            {
                std::string texturePath = utils::FileDialogs::OpenFile("");
                if (texturePath != "")
                {
                    if (name == "Albedo")
                        material.albedoMap = Core::TextureLoader::LoadTexture(texturePath, true);
                    else if (name == "Normal")
                        material.normalMap = Core::TextureLoader::LoadTexture(texturePath, true);
                    else if (name == "Metallic")
                        material.metallicMap = Core::TextureLoader::LoadTexture(texturePath, true);
                    else if (name == "Roughness")
                        material.roughnessMap = Core::TextureLoader::LoadTexture(texturePath, true);
                    else if (name == "AO")
                        material.aoMap = Core::TextureLoader::LoadTexture(texturePath, true);
                }
            }

            
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
                ImGui::Image((ImTextureID)texture, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
                ImGui::EndTooltip();
            }
        }
        ImGui::SameLine();
	}
}