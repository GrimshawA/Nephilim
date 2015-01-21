#ifndef NephilimFoundationPackage_h__
#define NephilimFoundationPackage_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

class PackageBuilder;
/**
	\class Package
	\brief This class allows to open a package, inspect its contents and load assets out of it
*/
class NEPHILIM_API Package
{
public:
	/// Constructs an uninitialized package reader
	Package();

	/// Constructs directly from a package file
	Package(const String& source);

	/// Attempts to extract the package contents to a directory
	bool extract(const String& directory);

private:
	String m_file; ///< The package source file

	friend class PackageBuilder;

	struct pFile
	{
		Int64 m_offset;
		Int64 m_length;
		String m_name;
	};

	struct pHeader
	{
		std::vector< pFile > m_files;
	};

	pHeader m_header;
};

/**
	\ingroup Core
	\class PackageBuilder
	\brief This class is able to generate package files.
*/
class NEPHILIM_API PackageBuilder
{
public:

	/// Adds a file to the package builder
	void addFile(const String& source, const String& destination);

	/// Generates the final package
	bool build();

private:
	std::vector<std::pair<String,String> > m_files; ///< The files queued for adding
	Package::pHeader m_header; ///< Header struct to fill
};

NEPHILIM_NS_END
#endif // NephilimFoundationPackage_h__
