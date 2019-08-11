[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/mortennobel/SimpleRenderEngine/master/LICENSE)
# RenderX

<div align=center><img src="https://github.com/project-William/RenderX/blob/master/Logo/Logo.png" width= "250" height="150"></div>

RenderX is a real-time and physically based rendering engine which built by C++ and Modern OpenGL.The goal of RenderX engine is to provide an easy way to get started with simple computer graphics programming even without a deep knowledge about the low-level graphics API like OpenGL.

RenderX currently depends on OpenGL 4.1(or higher),Dear ImGui(UI),glm(Math library), GLAD+GLFW,stb(loading textures) and runs on Windows.

----

## ScreenShot
<div align=center><img src="https://github.com/project-William/RenderX/blob/master/Gallery/ScreenShots.png" width= "800" height="480"></div>

## Gallery

![PhongModel](https://github.com/project-William/RenderX/blob/master/Gallery/PhongModel.jpg)|![LightingPBR](https://github.com/project-William/RenderX/blob/master/Gallery/LightingPBR.jpg)|![TexturePBR](https://github.com/project-William/RenderX/blob/master/Gallery/TexturePBR.jpg)



Dependencies:
 + [[glfw]](https://github.com/glfw/glfw):Window & input system
 + [[glad]](https://github.com/Dav1dde/glad):OpenGL funciton loader
 + [[Imgui]](https://github.com/ocornut/imgui):UI system
 + [[glm]](https://github.com/Groovounet/glm-deprecated):OpenGL math function
 + [[stb]](https://github.com/nothings/stb):Image loader

----

## Features
Objectives         |Implemented
:-----------------:|:---------------------:
Camera             |Movement,Zoom,FPS Game mode
Textures           |Cubemap,2DTexture init/load/bind
Mesh loading       |TODO:
Math               |by glm
Transformations    |Position TODO:
Lighting           |Basic
PBR                |Light and Texture PBR
Materials          |metallic,roughness
Deferred rendering |TODO
SSAO               |TODO
Normal mapping     |TODO
Shadow Mapping     |TODO
IBL                |TODO
Bloom              |TODO
Environment Reflection |TODO
MSAA               |Enable

----
 ## In the future..
 1:Cross-Platform feature
 2:More APIS:Vulkan DirectX
 3:......

  
