#ifndef PARABOLA_PACKAGES_H
#define PARABOLA_PACKAGES_H

#include "Platform.h"
#include "StringList.h"
#include "FileStream.h"
#include <map>
#include <SFML/System.hpp> // For input stream

PARABOLA_NAMESPACE_BEGIN

	/// Holds the engine's types of files.
	namespace SupportedFileTypes{
		/// Hint to the resource manager on how to load something from a package
		enum EngineFileTypes{ 
			Package = 0,
			Image,
			Texture,
			ParticlesXML,
			ParticlesBinary,
			SoundBuffer,
			Music,
			UserData
		};
	};

	/**
		\ingroup Foundation
		\class PackageFileInformation
		\brief Holds data about one file contained within a package
	*/
	class PARABOLA_API PackageFileInformation{
	public:

		/// Saves the file data into the stream
		void save(FileStream *fileStream);
		/// Loads the file data from the stream
		void load(FileStream *fileStream);
		/// Increments size with the size of the data this class owns. The size comes in bytes.
		void computeSize(unsigned long &size);

		/// The original path
		String path;
		/// An alias for this file
		String alias;
		/// An extension to specify the file type
		String fileType;
		/// User data to attach to this file
		String userData;
		/// Offset of the file in the package
		Int64 begin;
		/// Size in bytes of the file in the package
		Int64 size;
	
	};

	/**
		\ingroup Foundation
		\class PackageNode
		\brief Represents a directory in a package

		A package is for all effects a reduced file system, 
		therefore you can build a hierarchy of your choice under one package file.

		Each directory in a package is represented by a node. 
		A node, as being a virtual directory, can have child directories and files contained within.

		A PackageHeader always has at least one node, the root directory, which has no name.		
	*/
	class PARABOLA_API PackageNode{
	public:

		/// Fills in the passed vector with all file's original paths.
		void makeFileList(std::vector<PackageFileInformation> &vec);

		/// Debug function to print the file hierarchy.
		void printContents(String directory = "root");

		/// Saves its data to the stream and requests its child nodes to do the same.
		void save(FileStream *fileStream);
		/// Loads its data from the stream and requests its child nodes to do the same.
		void load(FileStream *fileStream);

		/// Increments size with the size of the data this class owns. The size comes in bytes.
		void computeSize(unsigned long &size);
		/// Computes the positions of all files in the hierarchy.
		/// After knowing the size in bytes of the header, it is possible to calculate where all files will be written.
		/// This is crucial for later accessing the files in the proper places when reading from the package.
		void computeOffsets(unsigned long &from);

		/// Name of this virtual directory
		String name;
		/// Map that matches a subdirectory name to the actual PackageNode structure.
		std::map<String, PackageNode> children;
		/// Map that matches the chosen in-package file name to a structure containing information about the file.
		std::map<String, PackageFileInformation> childFiles;
	};


	/**
		\ingroup Foundation
		\class PackageHeader
		\brief Represents the header information of a package file.

		Packages are pretty much a big file that contains a header and raw files within it.
		
		Header information is essential to locate the bounds of each file within the contiguous array of data.

		Other information about the package and its files is also recorded in it.

		Most importantly, it also holds data on the file hierarchy, so that you can have a reduced file system within the package.

	*/
	class PARABOLA_API PackageHeader{
	public:
		/// Creates the empty header structure
		PackageHeader();

		/// Saves the header into the stream
		bool save(FileStream *fileStream);
		/// Loads the header from the stream
		bool load(FileStream *fileStream);

		/// Finds a file's information within the package file system.
		/// If the file is not found it returns NULL.
		/// Note: you may use directories normally such as /images/myimage.png
		PackageFileInformation* findFile(String path);

		/// Compute the real offsets for all files in the hierarchy
		/// The computed values are calculated based on what will be written to the package file.
		void computeOffsets();

		/// The root directory
		PackageNode root;

		/// Computed header byte size
		unsigned long packageHeaderSize;
	};

	/**
		\ingroup Foundation
		\class PackageBuilder
		\brief An utility class to build package files.

		This class is basically a tool to help you assemble a package file from your resources.

		It will let you pick whatever files, directories and other packages you want,
		to build a new package from them.

		It does everything automatically, so you don't have to worry.

		Its usage would be something close to
		1. Choose file/directory/package to include in the package
		2. Choose how the resource from 1. will be known as in the package. (If you skip this, the file will be in the root)
		3. Repeat
		4. Build !

		\code
			PackageBuilder builder("package.pack");
			// Takes the file passed in parameter 1 to be included in the package, known as the parameter 2
			builder.addFile("images/monster1.png", "/monsters/grizzlybear");
			// Will put the file in the package, and it will be known as /monster2.png or simply, monster2.png
			builder.addFile("images/monster2.png");
			// Adds all "images" content into the package, under monster_images directory.
			// The directory content will be known as /monster_images/...
			builder.addDirectory("images", "monster_images");
			// Same as previous, but resources will be known as /images/
			builder.addDirectory("images");
			// Adding packages is similar to directories.
			
			//Finish the operation by building the package.
			builder.createPackage();
		\endcode

		\note Every time you try to add a file that already exists in the package, renaming will be attempted and a warning is logged.
	*/
	class PARABOLA_API PackageBuilder{
	public:
		/// Creates an empty PackageBuilder. Setting a name will be needed later.
		PackageBuilder();
		/// Creates an empty PackageBuilder, with the package name already set.
		PackageBuilder(const String &packageName);

		/// Adds the files to the package definition for later copy
		/// All the files passed in will have no aliases.
		void addFiles(StringList files);

		/// Adds the file to the package definition for later copy
		void addFile(String sourceFile, String destName = "");

		/// Adds a whole directory to the package definition
		void addDirectory(String directory);

		/// Actually creates the package
		bool createPackage();

	private:
		String packageName;
		PackageHeader header;
	};

	/**
		\ingroup Foundation
		\class PackageStream
		\brief Allows to read from a package

		This class is made to interface with a package, 
		providing the tools to access any file within the package file system.

		It also provides protection from reading bytes out-of-bounds, so it is safe to read data at will.

		You need to create such a stream out of a package name.

		Once you "own" that package, you need to seek a valid file by calling seekFile(String).
		Once you are over a valid file, you can read its data with ease!

		Sample usage:
		\code
			PackageStream stream("package.pack");
			stream.seekFile("/images/monster.png");
			// stream.read() at will!
		\endcode

		To finalise, it is to be noted that this class inherits sf::InputStream.
		That means you can load SFML resources directly from packages.
	*/
	class PARABOLA_API PackageStream : public DataStream, public sf::InputStream{
	public:
		/// Creates a stream to read from files contained within packages
		PackageStream();
		/// Creates a stream to read from files contained within packages
		PackageStream(String packageName);

		/// Travels within the package to the beginning of the desired file.
		/// Additionally, it creates a lock so you can read the file as it wasn't in a package.
		bool seekFile(String fileName);

		/// Debug function to print the whole file in the stdout
		void printFile();

		/// Debug function to copy the file data into a single file again
		void dumpFile(String destination);

		/// Debug function to print in the stdout the package hierarchy
		void dumpPackageContents();

		/// Allows to extract the package contents into single files again
		/// Depending on the value of keepOriginalPaths, you can either extract the package contents
		/// as their internal hierarchy was, or as they were originally, before being in a package.
		void extractPackage(String where, bool keepOriginalPaths);

	protected:
		/// sf::InputStream inherited
		virtual Int64 Read(char *data, Int64 byte_len);
		/// sf::InputStream inherited
		virtual Int64 Seek(Int64 position);
		/// sf::InputStream inherited
		virtual Int64 Tell();
		/// sf::InputStream inherited
		virtual Int64 GetSize();

	private:
		PackageHeader header;
		String packageName;
		FileStream *openStream;
		unsigned long sizeConstraint, offset;
	};


PARABOLA_NAMESPACE_END
#endif