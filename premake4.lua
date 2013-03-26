-- Hollow Engine Premake Script

local libname = "nephilim"
local enginename = "NephilimEngine"
local action = _ACTION or ""
local version = "0.8.3"

newoption {
   trigger     = "samples",
   description = "Makes project files for the samples"
}

solution (enginename)
	location("Build/" .. action)
	configurations { "Debug", "Release" }
	defines ( "ENGINE_VERSION_STRING=" .. version)
	
	project (enginename)
		language "C++"
		kind "StaticLib"
		includedirs { "Include" , "IncludeExt"}
		files { "Source/*.cpp" }
		files { "Include/*.h" }
		targetdir("Lib")
		
		configuration "Debug"
			defines { "_DEBUG" , "DEBUG" }
			flags { "Symbols" }
			targetname(libname .. "-d")
			
		configuration "Release"
			targetname(libname)
			flags { "Optimize" }
			
			
			
	-- Prepare the sample projects	
	configuration "samples"
		project "SampleBasic"
			language "C++"
			kind "ConsoleApp"
				