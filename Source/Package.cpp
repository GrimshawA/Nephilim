#include <Nephilim/Package.h>
#include <Nephilim/ScopedFile.h>
#include <Nephilim/DataStream.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Constructs an uninitialized package reader
Package::Package()
{

}

/// Constructs directly from a package file
Package::Package(const String& source)
: m_file(source)
{
	
}

/// Attempts to extract the package contents to a directory
bool Package::extract(const String& directory)
{
	ScopedFile file(m_file, IODevice::BinaryRead);
	if(file.isReady())
	{
		DataStream in(file);
		Int64 fileCount = 0;
		in >> fileCount;
		m_header.m_files.resize(fileCount);
		for(size_t i = 0; i < m_header.m_files.size(); i++)
		{
			in >> m_header.m_files[i].m_name >>  m_header.m_files[i].m_offset >>  m_header.m_files[i].m_length;
		}

		for(size_t i = 0; i < m_header.m_files.size(); i++)
		{
			ScopedFile srcFile(file.getHandle(), m_header.m_files[i].m_offset, m_header.m_files[i].m_length);			
			ScopedFile dstFile(directory + "/" + m_header.m_files[i].m_name, IODevice::BinaryWrite);
			cout << "Extracting("<< m_header.m_files[i].m_length  << "): " << directory + "/" + m_header.m_files[i].m_name << endl;
			if(srcFile.isReady() && dstFile.isReady())
				File::copy(srcFile, dstFile);
		}
	}

	

	return true;
}

/// Adds a file to the package builder
void PackageBuilder::addFile(const String& source, const String& destination)
{
	m_files.push_back(std::make_pair(source, destination));

	Package::pFile file;
	file.m_length = File::size(source);
	file.m_name = destination;
	m_header.m_files.push_back(file);
}

/// Generates the final package
bool PackageBuilder::build()
{
	bool success = false;

	ScopedFile file("package.pkg", IODevice::BinaryWrite);
	if(file.isReady())
	{
		Int64 headerSize = sizeof(Int64);
		for(unsigned int i = 0; i < m_header.m_files.size(); i++)
		{
			headerSize += sizeof(Int64) * 3 + sizeof(char) * m_header.m_files[i].m_name.length();
		}

		// Calculate offsets
		Int64 relOffset = headerSize;
		for(unsigned int i = 0; i < m_header.m_files.size(); i++)
		{
			m_header.m_files[i].m_offset = relOffset;
			relOffset += m_header.m_files[i].m_length;
		}

		// Write the header
		DataStream out(file);
		out << static_cast<Int64>(m_header.m_files.size());
		for(unsigned int i = 0; i < m_header.m_files.size(); i++)
		{
			out << m_header.m_files[i].m_name << m_header.m_files[i].m_offset << m_header.m_files[i].m_length;
		}

		for(std::vector<std::pair<String,String>>::iterator it = m_files.begin(); it != m_files.end(); ++it)
		{
			String source = it->first;
			String dest   = it->second;

			ScopedFile in(source, IODevice::BinaryRead);
			if(in.isReady())
			{
				/// Writes in contents to out
				File::copy(in, file);
			}
		}

		success = true;
	}

	return success;
}

NEPHILIM_NS_END