#include "test.h"
#include "graphics/Shader.h"
#include "Window.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "vendor/stb_image.h"


namespace renderx
{
	using namespace graphics;
	std::shared_ptr<Test> Test::m_Instance;
	std::shared_ptr<Test> Test::Create()
	{
		return std::shared_ptr<Test>(new Test());
	}

	void Test::HdrTexture()
	{
		//stbi_set_flip_vertically_on_load(true);
		//int width, height, nrComponents;
		//float* data = stbi_loadf("resources/textures/hdr/newport_loft.hdr", &width, &height, &nrComponents, 0);
		//if (data)
		//{
		//	glGenTextures(1, &hdrTexture);
		//	glBindTexture(GL_TEXTURE_2D, hdrTexture);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float
		//
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//
		//	stbi_image_free(data);
		//}
		//else
		//{
		//	std::cout << "Failed to load HDR image." << std::endl;
		//}

	}

	void Test::EnvMap()
	{
		glGenTextures(1, &envCubemap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // enable pre-filter mipmap sampling (combatting visible dots artifact)
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	void Test::equ(std::shared_ptr<graphics::Shader> equ, unsigned int hdr)
	{
		equ->BindShaderProgram();
		equ->SetInt("equirectangularMap", 0);
		equ->SetMat4("projection", captureProjection);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, hdr);

	}

	void Test::GererateMipmap(unsigned int cubemap)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	void Test::IrrdianceMap()
	{
		glGenTextures(1, &irradianceMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	void Test::BindEnvMap(unsigned int cubemap)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	}

	void Test::Prefilter()
	{
		glGenTextures(1, &prefilterMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minifcation filter to mip_linear 
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	}

	void Test::BRDF()
	{
		glGenTextures(1, &brdfLUTTexture);

		// pre-allocate enough memory for the LUT texture.
		glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
		// be sure to set wrapping mode to GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Test::fbo(std::shared_ptr<entity::Camera> cam,
		std::shared_ptr<graphics::Shader> pbr,
		std::shared_ptr<graphics::Shader> equ,
		std::shared_ptr<graphics::Shader> irr,
		std::shared_ptr<graphics::Shader> pre,
		std::shared_ptr<graphics::Shader> brd,
		std::shared_ptr<graphics::Shader> bac,
		std::function<void()> func1,
		unsigned int fbo,unsigned int rbo
	)
	{
		// lights
		// ------
		// pbr: setup framebuffer
		// ----------------------
		//unsigned int captureFBO;
		//unsigned int captureRBO;
		//glGenFramebuffers(1, &fbo);
		//glGenRenderbuffers(1, &rbo);
		//
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
		// pbr: load the HDR environment map
		// ---------------------------------
		
		// pbr: setup cubemap to render to and attach to framebuffer
		// ---------------------------------------------------------
		
		// pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
		// ----------------------------------------------------------------------------------------------
		
		
		// pbr: convert HDR equirectangular environment map to cubemap equivalent
		// ----------------------------------------------------------------------
		
		//glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//for (unsigned int i = 0; i < 6; ++i)
		//{
		//	equ->SetMat4("view", captureViews[i]);
		//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//
		//	renderCube();
		//}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
		
		//glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
		//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		
		// pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
		// --------------------------------------------------------------------------------

		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);
		
		// pbr: solve diffuse integral by convolution to create an irradiance (cube)map.
		// -----------------------------------------------------------------------------
		//irr->BindShaderProgram();
		//irr->SetInt("environmentMap", 0);
		//irr->SetMat4("projection", captureProjection);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
		
		//glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//for (unsigned int i = 0; i < 6; ++i)
		//{
		//	irr->SetMat4("view", captureViews[i]);
		//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//
		//	renderCube();
		//}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
		// --------------------------------------------------------------------------------
		
		// pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
		// ----------------------------------------------------------------------------------------------------
		//pre->BindShaderProgram();
		//pre->SetInt("environmentMap", 0);
		//pre->SetMat4("projection", captureProjection);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
		
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//unsigned int maxMipLevels = 5;
		//for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
		//{
		//	// reisze framebuffer according to mip-level size.
		//	unsigned int mipWidth = 128 * std::pow(0.5, mip);
		//	unsigned int mipHeight = 128 * std::pow(0.5, mip);
		//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
		//	glViewport(0, 0, mipWidth, mipHeight);
		//
		//	float roughness = (float)mip / (float)(maxMipLevels - 1);
		//	pre->SetFloat("roughness", roughness);
		//	for (unsigned int i = 0; i < 6; ++i)
		//	{
		//		pre->SetMat4("view", captureViews[i]);
		//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);
		//
		//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//		renderCube();
		//	}
		//}
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// pbr: generate a 2D LUT from the BRDF equations used.
		// ----------------------------------------------------
		
		
		// then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);
		//
		//glViewport(0, 0, 512, 512);
		//brd->BindShaderProgram();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//renderQuad();
		//
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		
		// initialize static shader uniforms before rendering
		// --------------------------------------------------
		auto window = Window::GetWindowInstance();;
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280/ (float)720, 0.1f, 100.0f);
		//pbr->BindShaderProgram();
		//pbr->SetMat4("projection", projection);
		//bac->BindShaderProgram();
		//bac->SetMat4("projection", projection);
		//
		//// then before rendering, configure the viewport to the original framebuffer's screen dimensions
		//int scrWidth, scrHeight;
		//glfwGetFramebufferSize(window->GetWinDataRef().glWindowPtr, &scrWidth, &scrHeight);
		//glViewport(0, 0, scrWidth, scrHeight);

		 //render loop
		 //-----------
		//float deltaTime = 0, lastFrame = 0;
		//while (!window->Closed())
		//{
		//	// per-frame time logic
		//	// --------------------
		//	float currentFrame = glfwGetTime();
		//	deltaTime = currentFrame - lastFrame;
		//	lastFrame = currentFrame;
		//
		//	// input
		//	// -----
		//	cam->EnableObject();
		//	
		//	// render
		//	// ------
		//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//
		//	// render scene, supplying the convoluted irradiance map to the final shader.
		//	// ------------------------------------------------------------------------------------------
		//	pbr->BindShaderProgram();
		//	glm::mat4 view = cam->GetViewMatrix();
		//	pbr->SetMat4("view", view);
		//	pbr->SetVec3("camPos", cam->GetCameraAttribRef().Position);
		//
		//	// bind pre-computed IBL data
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
		//	glActiveTexture(GL_TEXTURE1);
		//	glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
		//	glActiveTexture(GL_TEXTURE2);
		//	glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
		//
		//	// render rows*column number of spheres with material properties defined by textures (they all have the same material properties)
		//	glm::mat4 model = glm::mat4(1.0f);
		//	for (int row = 0; row < nrRows; ++row)
		//	{
		//		pbr->SetFloat("metallic", (float)row / (float)nrRows);
		//		for (int col = 0; col < nrColumns; ++col)
		//		{
		//			// we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
		//			// on direct lighting.
		//			pbr->SetFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));
		//
		//			model = glm::mat4(1.0f);
		//			model = glm::translate(model, glm::vec3(
		//				(float)(col - (nrColumns / 2)) * spacing,
		//				(float)(row - (nrRows / 2)) * spacing,
		//				-2.0f
		//			));
		//			pbr->SetMat4("model", model);
		//			renderSphere();
		//		}
		//	}
		//
		//
		//	// render light source (simply re-render sphere at light positions)
		//	// this looks a bit off as we use the same shader, but it'll make their positions obvious and 
		//	// keeps the codeprint small.
		//	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
		//	{
		//		glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		//		newPos = lightPositions[i];
		//		pbr->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
		//		pbr->SetVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
		//
		//		model = glm::mat4(1.0f);
		//		model = glm::translate(model, newPos);
		//		model = glm::scale(model, glm::vec3(0.5f));
		//		pbr->SetMat4("model", model);
		//		renderSphere();
		//	}
		//
		//	// render skybox (render as last to prevent overdraw)
		//	bac->BindShaderProgram();
		//	bac->SetMat4("view", view);
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
		//	//glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap); // display irradiance map
		//	//glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap); // display prefilter map
		//	renderCube();
		//
		//
		//	// render BRDF map to screen
		//	//brdfShader.Use();
		//	//renderQuad();
		//
		//
		//	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		//	// -------------------------------------------------------------------------------
		//	glfwSwapBuffers(window->GetWinDataRef().glWindowPtr);
		//	glfwPollEvents();
		//}
		

	}

	
	void Test::renderCube()
	{
		// initialize (if necessary)
		if (cubeVAO == 0)
		{
			float vertices[] = {
				// back face
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
			};
			glGenVertexArrays(1, &cubeVAO);
			glGenBuffers(1, &cubeVBO);
			// fill buffer
			glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			// link vertex attributes
			glBindVertexArray(cubeVAO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		// render Cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	// renderQuad() renders a 1x1 XY quad in NDC
	// -----------------------------------------
	void Test::renderQuad()
	{
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	// renders (and builds at first invocation) a sphere
// -------------------------------------------------

	void Test::renderSphere()
	{
		if (sphereVAO == 0)
		{
			glGenVertexArrays(1, &sphereVAO);

			unsigned int vbo, ebo;
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			std::vector<glm::vec3> positions;
			std::vector<glm::vec2> uv;
			std::vector<glm::vec3> normals;
			std::vector<unsigned int> indices;

			const unsigned int X_SEGMENTS = 64;
			const unsigned int Y_SEGMENTS = 64;
			const float PI = 3.14159265359;
			for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
			{
				for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
				{
					float xSegment = (float)x / (float)X_SEGMENTS;
					float ySegment = (float)y / (float)Y_SEGMENTS;
					float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
					float yPos = std::cos(ySegment * PI);
					float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

					positions.push_back(glm::vec3(xPos, yPos, zPos));
					uv.push_back(glm::vec2(xSegment, ySegment));
					normals.push_back(glm::vec3(xPos, yPos, zPos));
				}
			}

			bool oddRow = false;
			for (int y = 0; y < Y_SEGMENTS; ++y)
			{
				if (!oddRow) // even rows: y == 0, y == 2; and so on
				{
					for (int x = 0; x <= X_SEGMENTS; ++x)
					{
						indices.push_back(y * (X_SEGMENTS + 1) + x);
						indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					}
				}
				else
				{
					for (int x = X_SEGMENTS; x >= 0; --x)
					{
						indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
						indices.push_back(y * (X_SEGMENTS + 1) + x);
					}
				}
				oddRow = !oddRow;
			}
			indexCount = indices.size();

			std::vector<float> data;
			for (int i = 0; i < positions.size(); ++i)
			{
				data.push_back(positions[i].x);
				data.push_back(positions[i].y);
				data.push_back(positions[i].z);
				if (uv.size() > 0)
				{
					data.push_back(uv[i].x);
					data.push_back(uv[i].y);
				}
				if (normals.size() > 0)
				{
					data.push_back(normals[i].x);
					data.push_back(normals[i].y);
					data.push_back(normals[i].z);
				}
			}
			glBindVertexArray(sphereVAO);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			float stride = (3 + 2 + 3) * sizeof(float);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
		}

		glBindVertexArray(sphereVAO);
		glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
	}



}