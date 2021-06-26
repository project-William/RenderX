#include "pch.h"
#include "RendererPropEditor.h"
#include "MaterialEditor.h"
#include "../Core/RenderScene.h"
#include "SceneHierarchyPanel.h"
#include "ViewportWindow.h"
#include "../Base/Camera.h"

namespace renderx::ui
{

    std::shared_ptr<RendererPropEditor> RendererPropEditor::s_Instance;

    std::shared_ptr<RendererPropEditor>& RendererPropEditor::Get()
    {
        if (!s_Instance)
        {
            s_Instance = std::shared_ptr<RendererPropEditor>(new RendererPropEditor());
        }

        return s_Instance;
    }


    static void HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

	RendererPropEditor::RendererPropEditor()
	{

	}

	RendererPropEditor::~RendererPropEditor()
	{

	}


    void RendererPropEditor::UpdateTexture()
    {

    }

    void RendererPropEditor::UpdateTransformation(const std::string& name)
    {
       
        //auto renderer = Core::RenderScene::Get()->GetRenderersRef().find(name);
        ////transform			
        //if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        //{
        //    
        //
        //    float a[3] = { 1.0f,1.0f,1.0f };
        //    ImGui::Columns(2);
        //    ImGui::Text("Translation");
        //    ImGui::NextColumn();
        //    ImGui::PushItemWidth(-1);
        //    bool updateTransform = false;
        //
        //    if (ImGui::DragFloat3("##translation", a, 0.25f))
        //    {
        //        updateTransform = true;
        //    }
        //
        //    ImGui::PopItemWidth();
        //    ImGui::NextColumn();
        //
        //    ImGui::Text("Rotation");
        //    ImGui::NextColumn();
        //    ImGui::PushItemWidth(-1);
        //
        //    if (ImGui::DragFloat3("##rotation", a, 0.25f))
        //    {
        //        updateTransform = true;
        //    }
        //
        //    ImGui::PopItemWidth();
        //    ImGui::NextColumn();
        //
        //    ImGui::Text("Scale");
        //    ImGui::NextColumn();
        //    ImGui::PushItemWidth(-1);
        //
        //    if (ImGui::DragFloat3("##scale", a, 0.25f))
        //    {
        //        updateTransform = true;
        //    }
        //
        //    ImGui::PopItemWidth();
        //    ImGui::NextColumn();
        //    ImGui::Columns(1);
        //}
        //ImGui::Separator();
    }

    void RendererPropEditor::ColorPicker(const std::string& name)
    {
        
        auto& material = Core::RenderScene::Get()->GetRenderersMaterialMapRef().find(name)->second;
        //color
        if (ImGui::CollapsingHeader("Color Picker", ImGuiTreeNodeFlags_DefaultOpen))
        {

            //static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
            static ImVec4 defaultColor(0.8f, 0.8f, 0.8f, 1.0f);

            static bool alpha_preview = false;
            static bool alpha_half_preview = false;
            static bool drag_and_drop = true;
            static bool options_menu = false;
            static bool hdr = true;
            ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
            static bool no_border = false;
            static bool alpha = false;
            static bool alpha_bar = false;
            static bool side_preview = true;
            static int display_mode = 0;
            static int picker_mode = 0;
            ImGuiColorEditFlags flags = misc_flags;
            if (!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
            if (alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
            if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
            //if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
            //if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
            //if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
            //if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
            //if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
            //ImGui::ColorPicker4("Current##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);
            ImGui::ColorPicker4("", (float*)&material.color, flags, &defaultColor.x);
            
        }
    }

	void RendererPropEditor::RunPropEditor()
	{
        //auto& rendererListRef = Core::RenderScene::Get()->GetRenderersRef();
        auto selectedName = SceneHierarchyPanel::Get()->GetRendererName();

        static bool open = true;
		if (ImGui::Begin("Properties", &open, ImGuiWindowFlags_NoScrollbar))
		{
            if (selectedName!="")
            {
                ImGui::Columns(2, NULL, true);
                ImGui::Text("Name:"); ImGui::SameLine(); ImGui::Text(selectedName.c_str()); ImGui::SameLine();
                ImGui::NextColumn();

                ImGui::PushID(0);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.9f, 0.9f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 1.0f, 1.0f));
                if (ImGui::Button("Delete"))
                {
                    Core::RenderScene::Get()->RemoveRenderer(selectedName);
                    SceneHierarchyPanel::Get()->SetRendererName("");
                }
                ImGui::SameLine();
                if (ImGui::Button("Copy"))
                {


                }



                ImGui::PopStyleColor(3);
                ImGui::PopID();
                ImGui::Spacing();
                ImGui::NextColumn();

                auto& materialRef = Core::RenderScene::Get()->GetRenderersMaterialMapRef().find(selectedName);

                if (materialRef!=Core::RenderScene::Get()->GetRenderersMaterialMapRef().end())
                {

                    ImGui::RadioButton("pbr_color", &materialRef->second.switchShader, 0);
                    ImGui::NextColumn();
                    ImGui::RadioButton("pbr_texture", &materialRef->second.switchShader, 1);
                
                    ImGui::Columns();

                    static float a = 0;
                    ImGui::SliderFloat("Roughness", &materialRef->second.roughness, 0.0f, 1.0f);
                    ImGui::SliderFloat("Metallic", &materialRef->second.metallic, 0.0f, 1.0f);

                }
                

                if (materialRef != Core::RenderScene::Get()->GetRenderersMaterialMapRef().end())
                {
                    if(materialRef->second.switchShader == Core::ShaderType::PBR_COLOR)
                        ColorPicker(selectedName);
                    else
                        MaterialEditor::RunMatrialEditor(selectedName);

                }

              


            }


            UpdateTransformation(selectedName);

            //Core::Renderer& renderer = nullptr  ;
            //if (rendererListRef.size() != 0)
            //{
            //    auto& rendererListRef.find(selectedName) == rendererListRef.end())
            //
            //}

            
			
            ImGui::Spacing();
            ImGui::End();
		}
	}

}