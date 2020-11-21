varakdir = "%{wks.location}/varak"

project "Varak"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetdir ("%{outputdir}/%{prj.name}")
	objdir ("%{outputdir}/premake_files/%{prj.name}")

	pchheader "vrpch.h"
	pchsource "src/vrpch.cpp"

	files 
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"src",
		
		"%{vendordir}/spdlog/include",
		"%{vendordir}/glad/include",
		"%{vendordir}/glfw/include",
		"%{vendordir}/glm",
		"%{vendordir}/imgui",
        "%{vendordir}/stb_image",
		"%{vendordir}/entt"
	}

	links
	{
		"ImGui",
		"Glad",
        "GLFW",
        "stb_image"
	}

	filter "configurations:Debug"
		defines "VR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "VR_DISTRIBUTION"
		runtime "Release"
		optimize "on"

	filter "action:vs*" 
        buildoptions {"/FI vrpch.h"}
