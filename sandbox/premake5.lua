project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetdir ("%{outputdir}/%{prj.name}")
	objdir ("%{outputdir}/premake_files/%{prj.name}")

	files 
	{
		"src/**.h"
		"src/**.cpp"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	includedirs 
	{
		"%{varakdir}/src",
		
		"%{vendordir}/spdlog/include"
		"%{vendordir}/glm"
	}

	links
	{
		"Varak"
	}

	filter "configurations:Debug"
		define "VR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		define "VR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		define "VR_DISTRIBUTION"
		runtime "Release"
		optimize "on"
