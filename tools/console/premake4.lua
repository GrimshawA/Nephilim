
newoption {
	trigger		= "libs",
	value		= "path",
	description = "Tell where to look for the linking libraries"
}

solution "NephilimConsole"

	location "build"
	
	project "NephilimConsole"
		
		kind "ConsoleApp"
		configurations { "Debug" , "Release" }
		language "C++"
		targetdir  "bin" 
		
		files { "source/*" }
		includedirs { "../../include" , "../../includeext"}
		libdirs { "../../lib/" }
		libdirs { _OPTIONS["libs"] }
		
		configuration "Debug"
			defines { "_DEBUG" , "DEBUG" }
			flags { "Symbols" }
			targetname("nc_debug")
		
			links { "nephilim-d" }
			links("sfml-system-s-d")
			links("sfml-window-s-d")
			links("sfml-graphics-s-d")
			links("angelscript-d")
			links("libsigcpp-d")
			links("glew")
			
		configuration "Release"
			targetname("nc")
			flags { "Optimize" }
			links { "nephilim" }
			links("sfml-system-s")
			links("sfml-window-s")
			links("sfml-graphics-s")
			links("angelscript")
			links("libsigcpp")
			links("glew")