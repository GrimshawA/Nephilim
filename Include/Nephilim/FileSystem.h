#ifndef PARABOLA_FILESYSTEM_H
#define PARABOLA_FILESYSTEM_H

#include "Platform.h"
#include "StringList.h"

#ifdef SetCurrentDirectory
#undef SetCurrentDirectory
#endif


PARABOLA_NAMESPACE_BEGIN
	/**
		\ingroup Foundation
		\class FileSystem
		\brief Provides tools for interacting with the underlying OS.

		Commonly used for scanning directories, listing files, creating new directories, etc.

		\todo Extend functionality.
	*/
	class PARABOLA_API FileSystem{
	public:
		/// Testing \todo make
		static String loadFileDialog();
		/// Testing \todo make
		static String saveFileDialog();

		/**
			\brief Scan a directory for files

			You can use this method to look for files under certain parameters in the hard drive.

			\param Directory where to look for the files. Relative to the executable path.
			\param Extension of the files allowed to be found. Wildcards allowed. "*" would mean all extensions.
			\param Recursive defines if the method will scan inner directories within the specified one.

			\return A StringList containing the paths to all files found

		*/
		static StringList scanDirectory(const String &Directory,
				const String &Extension, bool Recursive = false);


		/**
			\brief Lists all directories in the desired location.

			\param Location to look for directories
			\param Whether the result should keep the paths or just display a directory name.

			\return List of strings containing the actual found directories.
		*/
		static StringList directoryList(String Where, bool KeepRelativePath = true);

		/**
			\brief Checks if a specific file/place is a directory
		*/
		static bool isDirectory(String Directory);

		/**
			\brief Checks if a specific file/place is a regular file
		*/
		static bool isFile(String fileName);


		static String getDocumentsDirectory();

		/**
			\brief Creates a directory in the underlying file system.
		*/
		static bool makeDirectory(String Name);

		/**
			\brief Tells what is the application current directory.
			\todo
		*/
		static String currentDirectory();

		/// Get the path of the executable - could be similar to C:/Games/ or /home/games/
		static String getExecutableDirectory();

	private:
		static String myCurrentDirectory;
	};

PARABOLA_NAMESPACE_END

#endif