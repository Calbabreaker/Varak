workspace "Varak"
	architecture "x86_64"
	startproject "VarakEditor"

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

binDir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
objFilesDir = "%{wks.location}/obj_files/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
vendorDir = "%{wks.location}/vendor"

group "Vendor"
	include "vendor/glfw"
	include "vendor/glad"
	include "vendor/imgui"
    include "vendor/stb_image"
group ""

include "varak"
include "sandbox"
include "varak_editor"
