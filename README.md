[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/mortennobel/SimpleRenderEngine/master/LICENSE)
# RenderX

<div align=center><img src="https://github.com/project-William/RenderX/blob/master/Logo/Logo.png" width= "250" height="150"></div>


RenderX is an early-stage toy rendering engine for Windows which mainly built by OpenGL and C++(17), currently only a few features have been implemented.The goal of RenderX is to provide an easy way to get started with computer graphics programming even without a deep knowledge about the low-level graphics API like OpenGL.

----

## ScreenShot

<div align=center><img src="https://github.com/project-William/RenderX/blob/master/Gallery/Screen.jpg" width= "800" height="480"></div>

## Get Started
Dependencies:
 + [[glfw]](https://github.com/glfw/glfw):Window & input system
 + [[glad]](https://github.com/Dav1dde/glad):OpenGL funciton loader
 + [[Imgui]](https://github.com/ocornut/imgui):UI system
 + [[glm]](https://github.com/Groovounet/glm-deprecated):OpenGL math function
 + [[stb]](https://github.com/nothings/stb):Image loader

IDE : Visual Studio 2019 is recommended,now RenderX is untested on other development platforms.


Just clone the repository to the local destination using git order:
`git clone https://github.com/project-William/RenderX`
Open it in vs2019 then set Application as startup project

 ----

 ## Core Features


 Feature    | Introduction    |Implemented
 :---------:|:---------:|:-----------:
 ~~Phong Model~~|<div align=center><img src="https://github.com/project-William/RenderX/blob/master/Gallery/phong.png"></div>|YES
 IBL        |<div align=center><img src="https://github.com/project-William/RenderX/blob/master/Gallery/IBL.png"></div>|YES
 Shadow     |           |NO
 Bloom      |           |NO


## Plan

Core plan for RenderX is to create a 3D engine(or rendering lab platform).

### more features will be done
- Native rendering API support (DirectX? Vulkan?)
- 3D random terrain generation
- Volumetric cloud
- Volumetric lighting
- Ray tracer (real-time + off-line)








