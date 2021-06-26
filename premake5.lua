--premake5.lua

workspace "RenderX"

    architecture "x86"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "ImGui"
    location "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    ok, err = os.copyfile("%{prj.name}/dependencies/glad/src/glad.c", "%{prj.name}/src")

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src/imgui",
		"RenderX/dependencies/glad/include",
        "RenderX/dependencies",
		"RenderX/dependencies/GLFW/include"
    }

    links
    {
        "glfw3.lib",
        "opengl32.lib"
    }

    libdirs
    {
        "RenderX/dependencies/GLFW/lib-vc2019"
    }

    filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
	
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
	
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
	
		runtime "Release"
		optimize "on"



project "RenderX"
    location "RenderX"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "pch.h"
	pchsource "RenderX/src/pch.cpp"

   

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        
        "ImGui/src",
        "%{prj.name}/src",
		"%{prj.name}/dependencies/glad/include",
        "%{prj.name}/dependencies",
		"%{prj.name}/dependencies/GLFW/include",
		"%{prj.name}/dependencies/glm",
        "%{prj.name}/dependencies/modelAssimp"
    }

    links
    {
        "glfw3.lib",
        "opengl32.lib",
        "ImGui",
        "assimp.dll",
        "assimp.lib"
    }

    libdirs
    {
        "%{prj.name}/dependencies/GLFW/lib-vc2019",
        "%{prj.name}/dependencies/modelAssimp/assimp/dll",
        "%{prj.name}/dependencies/modelAssimp/assimp/lib"
    }

    filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
	
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
	
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
	
		runtime "Release"
		optimize "on"


        
project "Application"
        location "Application"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        ok, err = os.copyfile("RenderX/dependencies/glad/src/glad.c", "%{prj.name}/src")
        
        files
        {
            "%{prj.name}/src/**.h",
		    "%{prj.name}/src/**.cpp"
            
        }

        includedirs
	    {
            "ImGui/src",
	    	"RenderX/src",
    		"RenderX/dependencies/GLFW/include",
    		"RenderX/dependencies/glad/include",
            "RenderX/dependencies",
    		"RenderX/dependencies/glm",
            "RenderX/dependencies/modelAssimp"
	    }

        links
        {
            "RenderX",
            "opengl32.lib",
            "glfw3.lib",
            "ImGui",
            "assimp.dll",
            "assimp.lib"
        }
        

        libdirs
        {
            "RenderX/dependencies/GLFW/lib-vc2019",
            "RenderX/dependencies/modelAssimp/assimp/dll",
            "RenderX/dependencies/modelAssimp/assimp/lib"
        }
    

        filter "system:windows"
		systemversion "latest"
		
	    filter "configurations:Debug"
		    runtime "Debug"
		    symbols "on"

	    filter "configurations:Release"
		    runtime "Release"
		    optimize "on"

	    filter "configurations:Dist"
		    runtime "Release"
		    optimize "on"