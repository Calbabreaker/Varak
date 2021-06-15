project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetdir(binDir)
	objdir(objFilesDir)

	files 
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs 
	{
		"%{varakDir}/src",
		
		"%{vendorDir}/spdlog/include",
        "%{vendorDir}/glm",
        "%{vendorDir}/imgui",
		"%{vendorDir}/entt/include"
	}

	links
	{
		"Varak",
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
