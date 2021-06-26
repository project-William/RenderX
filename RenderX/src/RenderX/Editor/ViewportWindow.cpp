#include "pch.h"
#include "ViewportWindow.h"
#include "../Base/Window.h"
#include "../Base/Camera.h"
#include "../Core/RenderScene.h"
#include "SceneHierarchyPanel.h"
#include "../Base/Keyboard.h"
namespace renderx::ui
{
	std::shared_ptr<ViewportWindow> ViewportWindow::s_Instance;

	ViewportWindow::ViewportWindow()
	{

	}

	std::shared_ptr<ViewportWindow>& ViewportWindow::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::shared_ptr<ViewportWindow>(new ViewportWindow());
		}
		return s_Instance;
	}

	ViewportWindow::~ViewportWindow()
	{

	}

	void ViewportWindow::RunViewportWindow(Core::FrameBuffer& framebuffer)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });

		if (ImGui::Begin("viewport"))
		{
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize != *(glm::vec2*)&viewportPanelSize)
			{
				framebuffer.Resize(viewportPanelSize.x, viewportPanelSize.y);
				m_ViewportSize = { viewportPanelSize.x,viewportPanelSize.y };
				base::Camera::Get()->SetProjectionMatrix(viewportPanelSize.x, viewportPanelSize.y);
			}

			ImGui::Image((void*)framebuffer.GetColorAttachment(), ImVec2{ viewportPanelSize.x,viewportPanelSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

			auto keyboard = base::Keyboard::Get();


			auto& transform = Core::RenderScene::Get()->GetRenderersTransformRef().find(SceneHierarchyPanel::Get()->GetRendererName());
			//auto& rendererRef = Core::RenderScene::Get()->GetRenderersRef().find(SceneHierarchyPanel::Get()->GetRendererName());

			
			if (transform != Core::RenderScene::Get()->GetRenderersTransformRef().end())
			{
				auto& model = Core::RenderScene::Get()->GetRenderersMapRef().find("cube")->second;
				//std::cout << model->m_AABB.Center().x << "   " << model->m_AABB.Center().y << "    " << model->m_AABB.Center().z << std::endl;
				//std::cout << model->m_AABB.BoxMax.x << "   " << model->m_AABB.BoxMax.y << "    " << model->m_AABB.BoxMax.z << std::endl;
				//std::cout << model->m_AABB.Size().x << "   " << model->m_AABB.Size().y << "    " << model->m_AABB.Size().z << std::endl;


				ImGuizmo::SetDrawlist();
			
				float windowWidth = (float)ImGui::GetWindowWidth();
				float windowHeight = (float)ImGui::GetWindowHeight();
			
				
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
			
				//camera
				base::Camera::Get()->SetProjectionMatrix(viewportPanelSize.x, viewportPanelSize.y);
				glm::mat4 viewMatrix = base::Camera::Get()->GetViewMatrix();
				glm::mat4 projectionMatrix = base::Camera::Get()->GetProjectionMatrix();
			
				auto tf = transform->second.ModelMatrix;
			
				glm::vec3 translation;
				glm::vec3 rotation;
				glm::vec3 scale;
			

				if (keyboard->GetKeyCode(base::Keys::RX_KEY_1))
				{
					ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::WORLD, glm::value_ptr(tf));
					ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(tf), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));
					//rendererRef->second->Translation = translation;
					if (ImGuizmo::IsUsing())
					{
						transform->second.ModelMatrix = tf;
						transform->second.Translation = translation;
					}

				}
				else if (keyboard->GetKeyCode(base::Keys::RX_KEY_2))
				{
					ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), ImGuizmo::OPERATION::ROTATE, ImGuizmo::LOCAL, glm::value_ptr(tf));
					ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(tf), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));
					//rendererRef->second->Rotation = rotation;
					if (ImGuizmo::IsUsing())
					{
						transform->second.ModelMatrix = tf;
						transform->second.Rotation = rotation;

					}
			
				}
				else if (keyboard->GetKeyCode(base::Keys::RX_KEY_3))
				{
					ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), ImGuizmo::OPERATION::SCALE, ImGuizmo::LOCAL, glm::value_ptr(tf));
					ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(tf), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));
					//rendererRef->second->Scale = scale;
					if (ImGuizmo::IsUsing())
					{
						transform->second.ModelMatrix = tf;
						transform->second.Scale = scale;
					}
			
				}
				

			}


			
			
			ImGui::PopStyleVar();
			
			ImGui::End();

		}
	}


	


}