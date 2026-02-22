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
        "%{prj.name}/vendors/spdlog/include"
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
    cppdialect "C++17"
    staticruntime "on"
    
    defines {
    	"_CRT_SECURE_NO_WARNINGS",
        "AE_PLAT_WINDOWS"
    }
		
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"
    defines "AE_DEBUG"
	
filter "configurations:Release"
	runtime "Release"
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
        "arcane/vendors/spdlog/include"
    }

    links {
        "arcane"
    }

filter "system:windows"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "on"
    
    defines {
    	"_CRT_SECURE_NO_WARNINGS",
        "AE_PLAT_WINDOWS"
    }
		
filter "configurations:Debug"
	runtime "Debug"
	symbols "on"
    defines "AE_DEBUG"
	
filter "configurations:Release"
	runtime "Release"
	optimize "on"
    defines "AE_RELEASE"