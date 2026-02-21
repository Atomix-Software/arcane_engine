workspace "arcane_engine"
    filename "arcane_engine"
    architecture "x64"
    configurations { "Debug", "Release" }

    BUILD_FORMAT = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    startproject "arcane"

project "arcane"
    location "arcane"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    buildoptions { "/utf-8" }

    targetdir("bin/" .. BUILD_FORMAT .. "/%{prj.name}")
    objdir("bin-int/" .. BUILD_FORMAT .. "/%{prj.name}")

    files {
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h"
    }

filter "system:windows"
		systemversion "latest"
		
		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}
		
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"
	
filter "configurations:Release"
	runtime "Release"
	optimize "on"