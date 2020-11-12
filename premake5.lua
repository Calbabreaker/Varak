workspace "Varak"
	architecture "x86_64"
	startproject "Sandbox"

	configurations 
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
    }
    
    files 
    {
        ".clang-format",
        ".editorconfig"
    }

outputdir = "%{wks.location}/build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
vendordir = "%{wks.location}/vendor"

group "Vendor"
	include "vendor/glfw"
	include "vendor/glad"
	include "vendor/imgui"
	include "vendor/stb_image"
group ""

include "Varak"
include "Sandbox"
