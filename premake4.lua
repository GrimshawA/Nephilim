-- Hollow Engine Premake Script

local libname = "nephilim"
local enginename = "NephilimEngine"
local action = _ACTION or ""
local version = "0.8.3"
local samplelist = { "SampleBasic" }
	
newoption {
   trigger     = "no-samples",
   description = "Makes project files for the samples"
}

newoption {
	trigger		= "android",
	description = "Applicable for visual studio solutions. You need vs-android plugin."
}

newoption {
	trigger		= "outdir",
	value		= "path",
	description = "Changes the output directory of the project files"
}

local builddir = action
if _OPTIONS["outdir"] then
	builddir  = _OPTIONS["outdir"]
end

solution (enginename)
	location("Build/" .. builddir)
	configurations { "Debug", "Release" }
	defines ( "ENGINE_VERSION_STRING=" .. version)
	defines { "MINIMAL_BUILD" }
	
	project (enginename)
		language "C++"
		kind "StaticLib"
		includedirs { "Include" , "IncludeExt"}
		files { "Source/*.cpp" }
		files { "IncludeExt/AS/AS*.cpp" }
		files { "Include/Nephilim/*.h" }
		targetdir("Lib")
		flags { "Unicode" }
		
		if table.contains(_ARGS, "--android") then
			if string.find(action, "vs*") then
				print("Android with Visual Studio detected, vs-android must be installed!\nChange the platform to Android and compile!")				
			end
			targetextension ".a"
		end
		
		configuration "Debug"
			defines { "_DEBUG" , "DEBUG" }
			flags { "Symbols" }
			targetname(libname .. "-d")
			
		configuration "Release"
			targetname(libname)
			flags { "Optimize" }
			
	project "NephilimConsole"
		language "C++"
		kind "ConsoleApp"
		files { "Tools/NephilimConsole/Source/*" }
		location("Build/" .. builddir)
		vpaths { ["Headers"] = "**.h" }
		vpaths { ["Source"] = "**.cpp" }
		includedirs { "Include" , "IncludeExt"}
		links (enginename)
		targetdir  "Bin" 
		
		if os.isdir("LibExt") then 
			libdirs { "LibExt/" .. builddir }
			links("sfml-system-s")
			links("sfml-window-s")
			links("sfml-graphics-s")
			links("angelscript")
			links("libsigcpp")
		end
		
	configuration "Debug"
		defines { "DEBUG" }
			
	-- Prepare the sample projects	
	if not table.contains(_ARGS, "--no-samples")  then
	for i=1 , # samplelist do
		local sample = samplelist[i]
		project (sample)
			language "C++"
			kind "ConsoleApp"
			location("Build/" .. builddir)
			vpaths { ["Headers"] = "**.h" }
			vpaths { ["Source"] = "**.cpp" }
			files { "Samples/" .. sample .. "/Source/*" }
			includedirs { "Include" , "IncludeExt"}
			links (enginename)
			targetdir  "Bin" 
			
			if os.isdir("LibExt") then 
				print("Found LibExt directory. Will attempt automatic linking to pre-compiled libraries")
				libdirs { "LibExt/" .. builddir }
			end
		
			if os.get() == "windows" and not table.contains(_ARGS, "--android") then
				links("opengl32")
			end
			
			configuration "Debug"
				flags { "Symbols" }
				
				if os.isdir("LibExt") then 
					links("sfml-system-s-d")
					links("sfml-window-s-d")
					links("sfml-graphics-s-d")
					links("angelscript-d")
					links("libsigcpp-d")
				end
				
			configuration "Release"			
				flags { "Optimize" }
				
				if os.isdir("LibExt") then 
					links("sfml-system-s")
					links("sfml-window-s")
					links("sfml-graphics-s")
					links("angelscript")
					links("libsigcpp")
				end
	end
	end
	