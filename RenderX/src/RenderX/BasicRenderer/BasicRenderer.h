#pragma once
#include "pch.h"	
#include "../Core/Shader.h"

namespace renderx::basicRenderer
{
	class BasicRenderer
	{
	public:
		static void RenderCube();
		static void RenderQuad();
		static void RenderSphere();
        static void renderScene(const Core::Shader& shader)
        {
            // room cube
            glm::mat4 model = glm::mat4(1.0f);
 
            
            //model = glm::mat4(1.0f);
            //shader.SetMat4("model", model);
            //RenderPlane();


            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
            model = glm::scale(model, glm::vec3(0.5f));
            shader.SetMat4("model", model);
            RenderCube();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
            model = glm::scale(model, glm::vec3(0.5f));
            shader.SetMat4("model", model);
            RenderCube();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
            model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
            model = glm::scale(model, glm::vec3(0.25));
            shader.SetMat4("model", model);
            RenderCube();
          
        }

    private:
        static unsigned int cubeVAO;
        static unsigned int cubeVBO;

        static unsigned int quadVAO;
        static unsigned int quadVBO;

        static unsigned int sphereVAO;
        static unsigned int sphereVBO;
        static unsigned int sphereEBO;
        static unsigned int indexCount;

        static unsigned int planeVBO;
        static unsigned int planeVAO;
        
    };
}