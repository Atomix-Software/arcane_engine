workspace "arcane_engine"
    filename "arcane_engine"
    architecture "x64"
    configurations { "Debug", "Release" }

    startproject "sandbox"

    OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["spdlog"] = "arcane/vendors/spdlog/include/"
    IncludeDir["GLFW"] = "arcane/vendors/glfw/include/"
    IncludeDir["GLAD"] = "arcane/vendors/glad/include/"
    IncludeDir["GLM"]  = "arcane/vendors/glm/"

    include "arcane/vendors/glfw"
    include "arcane/vendors/glad"

project "arcane"
    location "arcane"
    kind "SharedLib"
    language "C++"

    buildoptions { "/utf-8" }

    targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    pchheader "aepch.h"
    pchsource "arcane/src/aepch.cpp"

    files {
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h"
    }

    includedirs {
        "arcane/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLM}",
    }

    links {
        "glfw",
        "glad",
        "opengl32.lib"
    }

    defines {
        "AE_BUILD_DLL"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OUTPUT_DIR .. "/sandbox")
    }

filter "system:windows"
    systemversion "latest"
    cppdialect "C++20"
    staticruntime "on"
    
    defines {
    	"_CRT_SECURE_NO_WARNINGS",
        "AE_PLAT_WINDOWS"
    }
		
filter "configurations:Debug"
	runtime "Debug"
    buildoptions "/MDd"
	symbols "on"
    defines "AE_DEBUG"
	
filter "configurations:Release"
	runtime "Release"
    buildoptions "/MD"
	optimize "on"
    defines "AE_RELEASE"

project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"

    buildoptions { "/utf-8" }

    targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files {
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h"
    }

    includedirs {
        "arcane/src",
        "%{IncludeDir.spdlog}",
    }

    links {
        "arcane"
    }

filter "system:windows"
    systemversion "latest"
    cppdialect "C++20"
    staticruntime "on"
    
    defines {
    	"_CRT_SECURE_NO_WARNINGS",
        "AE_PLAT_WINDOWS"
    }
		
filter "configurations:Debug"
	runtime "Debug"
    buildoptions "/MDd"
	symbols "on"
    defines "AE_DEBUG"
	
filter "configurations:Release"
	runtime "Release"
    buildoptions "/MD"
	optimize "on"
    defines "AE_RELEASE"