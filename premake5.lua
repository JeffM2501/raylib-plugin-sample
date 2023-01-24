workspace "plugin-sample"
	configurations { "Debug.DLL", "Release.DLL" }
	platforms { "x64", "x86"}

	filter "configurations:Debug.DLL"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release.DLL"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
        
    filter { "platforms:x86" }
		architecture "x86"
		
	targetdir "bin/%{cfg.buildcfg}/"
	
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}
		
project "raylib"
		filter "configurations:Debug.DLL OR Release.DLL"
			kind "SharedLib"
			defines {"BUILD_LIBTYPE_SHARED"}
			
		filter "configurations:Debug OR Release"
			kind "StaticLib"
			
		filter "action:vs*"
			defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
			links {"winmm"}
			
		filter "action:gmake*"
			links {"pthread", "GL", "m", "dl", "rt", "X11"}
			
		filter{}
		
		location "build"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}"
		cppdialect "C++17"
		
		includedirs { "raylib/src", "raylib/src/external/glfw/include"}
		vpaths 
		{
			["Header Files"] = { "raylib/src/**.h"},
			["Source Files/*"] = {"raylib/src/**.c"},
		}
		files {"raylib/src/*.h", "raylib/src/*.c"}
		
project "app"
	kind "ConsoleApp"
	location "app"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	cppdialect "C++17"
	
	vpaths 
	{
		["Header Files"] = { "**.h"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	files {"app/**.c", "app/**.cpp", "app/**.h", "API/**.h"}

	links {"raylib"}
	
	includedirs {"raylib/src", "app", "API"}
	
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33", "INSIDE_APP"}
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		dependson {"raylib"}
		links {"raylib.lib", "winmm", "kernel32"}
		libdirs {"bin/%{cfg.buildcfg}"}
		characterset ("MBCS")
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
		
project "pluginA"
	kind "SharedLib"
	location "pluginA"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	cppdialect "C++17"
	dependson {"app"}
	
	vpaths 
	{
		["Header Files"] = { "**.h"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	files {"pluginA/**.c", "pluginA/**.cpp", "pluginA/**.h", "API/**.h"}

	links {"raylib", "app"}
	
	filter "action:vs*"
		links {"app.lib"}
		libdirs {"bin/%{cfg.buildcfg}"}
	
	includedirs {"raylib/src", "API"}
	
project "pluginB"
	kind "SharedLib"
	location "pluginB"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	cppdialect "C++17"
	dependson {"app"}
	
	vpaths 
	{
		["Header Files"] = { "**.h"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	files {"pluginB/**.c", "pluginB/**.cpp", "pluginB/**.h", "API/**.h"}

	links {"raylib", "app"}
	
	filter "action:vs*"
		links {"app.lib"}
		libdirs {"bin/%{cfg.buildcfg}"}
	
	
	includedirs {"raylib/src", "API"}


