-- Hollow Engine Premake Script

local libname = "nephilim"
local enginename = "NephilimEngine"
local action = _ACTION or ""
local version = "0.8.3"
local samplelist = { "SampleBasic" }

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
	if table.contains(_ARGS, "--samples")  then
	for i=1 , # samplelist do
		local sample = samplelist[i]
		project (sample)
			language "C++"
			kind "ConsoleApp"
			vpaths { ["Headers"] = "**.h" }
			vpaths { ["Source"] = "**.cpp" }
			files { "Samples/" .. sample .. "/Source/*" }
	end
	end
				