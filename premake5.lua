workspace "ArcaneEngine"
	filename "ArcaneEngine"
	architecture "x64"
	configurations {"Debug", "Release", "Distribution"}
	
	startproject "Grimoire"
	
	OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	ENGINE_INCLUDE_DIR = {}
	ENGINE_INCLUDE_DIR["GLM"]     = "Grimoire/vendors/Arcane/Arcane/vendors/glm"
	ENGINE_INCLUDE_DIR["SPD_LOG"] = "Grimoire/vendors/Arcane/Arcane/vendors/spdlog/include"
	ENGINE_INCLUDE_DIR["IMGUI"]   = "Grimoire/vendors/Arcane/Arcane/vendors/imgui"
	ENGINE_INCLUDE_DIR["ARCANE"]  = "Grimoire/vendors/Arcane/Arcane/src"
	
	group "Dependencies"
		include "Grimoire/vendors/Arcane/Arcane/vendors/glfw"
		include "Grimoire/vendors/Arcane/Arcane/vendors/glad"
		include "Grimoire/vendors/Arcane/Arcane/vendors/imgui"
		include "Grimoire/vendors/Arcane/Arcane/vendors/openal-soft"
		include "Grimoire/vendors/Arcane"
	
	group ""
	
project "Grimoire"
	location "Grimoire"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	buildoptions{"/utf-8"}
	
	targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
	objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")
	
	files 
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h"
	}
	
	includedirs 
	{
		"%{ENGINE_INCLUDE_DIR.ARCANE}",
		"%{ENGINE_INCLUDE_DIR.SPD_LOG}",
		"%{ENGINE_INCLUDE_DIR.IMGUI}",
		"%{ENGINE_INCLUDE_DIR.GLM}",
	}
	
	links {
		"Arcane"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "ARC_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "ARC_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Distribution"
		defines "ARC_DIST"
		runtime "Release"
		optimize "on"
		