project "stb_image"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    targetdir ("%{outputdir}/%{prj.name}")
	objdir ("%{outputdir}/premake_files/%{prj.name}")

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

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
