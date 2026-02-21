workspace "arcane_engine"
    filename "arcane_engine"
    architecture "x64"
    configurations { "Debug", "Release" }

    OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    startproject "arcane"

project "arcane"
    location "arcane"
    kind "SharedLib"
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

    defines {
        "ARC_BUILD_DLL"
    }

filter "system:windows"
    systemversion "latest"
    cppdialect "C++20"
    staticruntime "on"
    
    defines {
    	"_CRT_SECURE_NO_WARNINGS",
        "ARC_PLAT_WINDOWS"
    }
		
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"
    defines "ARC_DEBUG"
	
filter "configurations:Release"
	runtime "Release"
	optimize "on"
    defines "ARC_RELEASE"

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
        "arcane/src"
    }

    links {
        "arcane"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    }

filter "system:windows"
    systemversion "latest"
    cppdialect "C++20"
    staticruntime "on"
    
    defines {
    	"_CRT_SECURE_NO_WARNINGS",
        "ARC_PLAT_WINDOWS"
    }
		
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"
    defines "ARC_DEBUG"
	
filter "configurations:Release"
	runtime "Release"
	optimize "on"
    defines "ARC_RELEASE"