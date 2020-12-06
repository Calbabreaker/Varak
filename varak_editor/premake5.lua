project "VarakEditor"
	kind "ConsoleApp"
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
        "src/**.cpp",
        "src/panels/*.cpp"
    }

    defines
	{
        "_CRT_SECURE_NO_WARNINGS"
	}
    
	includedirs 
	{
		"%{varakdir}/src",
		
		"%{vendordir}/spdlog/include",
        "%{vendordir}/glm",
		"%{vendordir}/imgui",
		"%{vendordir}/entt"
	}

	links
	{
		"Varak"
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

