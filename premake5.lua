workspace "ArcaneEngine"
	filename "ArcaneEngine"
	architecture "x64"
	configurations {"Debug", "Release", "Distribution"}
	
	startproject "Playground"
	
	OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	INCLUDE_DIR = {}
	INCLUDE_DIR["GLFW"] = "Arcane/vendors/glfw/include"
	INCLUDE_DIR["GLM"] = "Arcane/vendors/glm"
	INCLUDE_DIR["GLAD"] = "Arcane/vendors/glad/include"
	INCLUDE_DIR["STB"] = "Arcane/vendors/stb"
	INCLUDE_DIR["SPD_LOG"] = "Arcane/vendors/spdlog/include"
	
	include "Arcane/vendors/glfw"
	include "Arcane/vendors/glad"
	
project "Arcane"
	location "Arcane"
	kind "SharedLib"
	language "C++"
	
	buildoptions{"/utf-8"}
	
	targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
	objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")
	
	pchheader "arcpch.h"
	pchsource "Arcane/src/arcpch.cpp"
	
	files 
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h"
	}
	
	includedirs 
	{
		"%{prj.name}/src",
		"%{INCLUDE_DIR.GLFW}",
		"%{INCLUDE_DIR.GLM}",
		"%{INCLUDE_DIR.GLAD}",
		"%{INCLUDE_DIR.STB}",
		"%{INCLUDE_DIR.SPD_LOG}"
	}
	
	links 
	{
		"glfw",
		"glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
	
		defines 
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE",
			"ARC_PLATFORM_WINDOWS",
			"ARC_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OUTPUT_DIR .. "/Playground")
		}
		
	filter "configurations:Debug"
		defines "ARC_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "ARC_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "ARC_DIST"
		buildoptions "/MD"
		optimize "On"
		
project "Playground"
	location "Playground"
	kind "ConsoleApp"
	language "C++"
	
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
		"Arcane/src",
		"%{INCLUDE_DIR.SPD_LOG}"
	}
	
	links {
		"Arcane"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
	
		defines 
		{
			"ARC_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "ARC_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "ARC_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "ARC_DIST"
		buildoptions "/MD"
		optimize "On"