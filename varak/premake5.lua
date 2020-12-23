varakDir = "%{wks.location}/varak"

project "Varak"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetdir(binDir)
	objdir(objFilesDir)

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
		
		"%{vendorDir}/spdlog/include",
		"%{vendorDir}/glad/include",
		"%{vendorDir}/glfw/include",
		"%{vendorDir}/glm",
		"%{vendorDir}/imgui",
        "%{vendorDir}/stb_image",
        "%{vendorDir}/entt/include",
		"%{vendorDir}/fontawesome/include"
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
