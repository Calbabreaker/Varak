project "stb_image"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

	targetdir(binDir)
	objdir(objFilesDir)

    files 
    {
        "**.h",
        "**.cpp"
    }

    includedirs 
    {
        "./"
    }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release or Distribution"
		runtime "Release"
		optimize "on"
