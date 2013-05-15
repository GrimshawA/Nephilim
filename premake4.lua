-- Nephilim Engine Premake Script
local libname = "nephilim"
local enginename = "NephilimEngine"
local action = _ACTION or ""
local version = "0.8.3"
local samplelist = { "LD26Kinectic", "SampleBasic" , "SampleAnimation", "SampleCameras", "SampleFileSystem", "SampleGeometry", "SampleKinesisPhysics", "SampleLighting", "SampleRenderTexture", "SampleScripting", "SampleShaders", "SampleSprites", "SampleUI" }
	
newoption {
   trigger     = "no-samples",
   description = "Don't generate sample projects."
}

newoption {
	trigger		= "android",
	description = "Configures for an android compilation under vs-android."
}

newoption {
	trigger		= "outdir",
	value		= "path",
	description = "Changes the output directory of the project files"
}

newoption {
	trigger = "lib",
	value = "path",
	description = "Link to libraries in the path"
}

newoption {
	trigger	= "gles2",
	description = "Prefer GLES 2.0 where applicable"
}

local builddir = action
if _OPTIONS["outdir"] then
	builddir  = _OPTIONS["outdir"]
end

solution (enginename)
	location("build/" .. builddir)
	configurations { "Debug", "Release" }
	defines ( "ENGINE_VERSION_STRING=" .. version)
	defines { "MINIMAL_BUILD" }
	
	project (enginename)
		language "C++"
		kind "StaticLib"
		includedirs { "include" , "includeext"}
		files { "source/*.cpp" }
		files { "includeext/AS/AS*.cpp" }
		files { "include/Nephilim/*.h" }
		targetdir("lib")
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
			

			
			
	-- Prepare the sample projects	
	if not table.contains(_ARGS, "--no-samples")  then
	for i=1 , # samplelist do
		local sample = samplelist[i]
		project (sample)
			language "C++"
			kind "ConsoleApp"
			location("build/" .. builddir)
			vpaths { ["Headers"] = "**.h" }
			vpaths { ["Source"] = "**.cpp" }
			files { "samples/" .. sample .. "/Source/*" }
			includedirs { "include" , "includeext"}
			links (enginename)
			targetdir  "bin" 

		
			if os.get() == "windows" and not table.contains(_ARGS, "--android") then
				links("opengl32")
			end


			if os.get() == "linux" then
				links("sfml-system")
				links("sfml-window")
				links("sfml-graphics")
				links("angelscript")
				links("sigc++")
				links("GLEW")
			end

			configuration "Debug"
				flags { "Symbols" }
				
				if os.isdir("LibExt") then 
					libdirs { "LibExt/" .. builddir }
					links("sfml-system-s-d")
					links("sfml-window-s-d")
					links("sfml-graphics-s-d")
					links("angelscript-d")
					links("libsigcpp-d")
				end
				
				-- Debug Android
				if table.contains(_ARGS, "--android") then		
					if table.contains(_ARGS, "--gles2") then linkoptions ( "-lGLESv2" ) else linkoptions ( "-lGLESv1_CM" ) end
					if _OPTIONS["lib"] then libdirs (_OPTIONS["lib"])
						linkoptions { "-lsigc++-d" }
					end	
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
	
