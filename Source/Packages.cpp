#ifndef MINIMAL_BUILD

#include "Nephilim/Packages.h"
#include "Nephilim/Sizes.h"
#include "Nephilim/FileSystem.h"

#include <iostream>

NEPHILIM_NS_BEGIN

void PackageFileInformation::save(FileStream *fileStream){
	*fileStream << path;
	*fileStream << alias;
	*fileStream << begin;
	*fileStream << size;

};

void PackageFileInformation::load(FileStream *fileStream){
	*fileStream >> path;
	*fileStream >> alias;
	*fileStream >> begin;
	*fileStream >> size;
};

void PackageFileInformation::computeSize(unsigned long &size){
	size += Sizes::getSize(path);
	size += Sizes::getSize(alias);
	size += sizeof(Int64);
	size += sizeof(Int64);
};


/************************************************************************/
/* Package Header                                                       */
/************************************************************************/

PackageHeader::PackageHeader(){
	packageHeaderSize = 0;
};

bool PackageHeader::save(FileStream *fileStream){

	if(packageHeaderSize == 0){
		computeOffsets();
	}

	//*fileStream << packageHeaderSize;

	//Save hierarchy
	root.save(fileStream);
	return true;
};

bool PackageHeader::load(FileStream *fileStream){
	root.load(fileStream);

	return true;
};

void PackageHeader::computeOffsets(){
	//calculate header size and correct all files.
	packageHeaderSize = 0;
	root.computeSize(packageHeaderSize);

	unsigned long files_begin = packageHeaderSize;
	root.computeOffsets(files_begin);

};



PackageFileInformation* PackageHeader::findFile(String path){
	StringList stripped_path = path.split("/");

	if(stripped_path.size() == 0)return NULL;
	else if(stripped_path.size() == 1){
		//only the file
		
		std::map<String, PackageFileInformation>::iterator it = root.childFiles.find(stripped_path[0]);
		if(it != root.childFiles.end()){
			return &it->second;
		}

	}
	else{
		PackageNode *node = &root;
		for(unsigned int i = 0; i < stripped_path.size()-1; i++){
			std::map<String, PackageNode>::iterator it = node->children.find(stripped_path[i]);
			if(it != node->children.end()){
				//found directory, proceed search
				node = &it->second;
			}
			else{
				return NULL; //invalid path
			}
		}

		std::map<String, PackageFileInformation>::iterator it = node->childFiles.find(stripped_path.back());
		if(it != node->childFiles.end()){
			return &it->second;
		}
		else return NULL; // doesnt exist.

	}

	return NULL;
};

/************************************************************************/
/* Package Node                                                         */
/************************************************************************/
void PackageNode::makeFileList(std::vector<PackageFileInformation> &vec){
	for(std::map<String, PackageFileInformation>::iterator it = childFiles.begin(); it != childFiles.end(); it++){
		vec.push_back(it->second);
	}

	for(std::map<String, PackageNode>::iterator it = children.begin(); it != children.end(); it++){
		it->second.makeFileList(vec);
	}
};

void PackageNode::computeSize(unsigned long &size){
	size += Sizes::getSize(name);

	size += sizeof(unsigned int);
	for(std::map<String, PackageFileInformation>::iterator it = childFiles.begin(); it != childFiles.end(); it++){
		size += Sizes::getSize(it->first);
		it->second.computeSize(size);
	}

	size += sizeof(unsigned int);
	for(std::map<String, PackageNode>::iterator it = children.begin(); it != children.end(); it++){
		it->second.computeSize(size);
	}
	
};

void PackageNode::computeOffsets(unsigned long &from){	
	for(std::map<String, PackageFileInformation>::iterator it = childFiles.begin(); it != childFiles.end(); it++){
		Int64 size = FileStream::size(it->second.path);
		it->second.begin = from;
		it->second.size = size;
		from += (unsigned long)size;
	}

	for(std::map<String, PackageNode>::iterator it = children.begin(); it != children.end(); it++){
		it->second.computeOffsets(from);
	}
};

void PackageNode::save(FileStream *fileStream){
	*fileStream << name;

	*fileStream << childFiles.size();
	for(std::map<String, PackageFileInformation>::iterator it = childFiles.begin(); it != childFiles.end(); it++){
		*fileStream << it->first;
		it->second.save(fileStream);
	}

	*fileStream << children.size();
	for(std::map<String, PackageNode>::iterator it = children.begin(); it != children.end(); it++){
		it->second.save(fileStream);
	}
};

void PackageNode::load(FileStream *fileStream){
	*fileStream >> name;

	//std::cout<<"Read Node: "<<name<<endl;
	
	unsigned int fileCount;
	*fileStream >> fileCount;

	for(unsigned int i = 0; i < fileCount; i++){
		//create the files
		String fileName;
		*fileStream >> fileName;

		PackageFileInformation file;
		file.load(fileStream);
		childFiles[fileName] = file;
	}


	unsigned int childCount;
	*fileStream >> childCount;

	for(unsigned int i = 0; i < childCount; i++){
		PackageNode node;
		node.load(fileStream);
		children[node.name] = node;
	}
};

void PackageNode::printContents(String directory){
	for(std::map<String, PackageFileInformation>::iterator it = childFiles.begin(); it != childFiles.end(); it++){
		std::cout << "File: "<<directory + it->first<<std::endl;
	}

	for(std::map<String, PackageNode>::iterator it = children.begin(); it != children.end(); it++){
		std::cout << "Directory: "<<it->second.name<<std::endl;
		it->second.printContents(directory + "/" + it->second.name);
	}
};

/************************************************************************/
/* Package Builder                                                      */
/************************************************************************/

PackageBuilder::PackageBuilder(){

};

PackageBuilder::PackageBuilder(const String &packageName){
	this->packageName = packageName;
};

void PackageBuilder::addFiles(StringList files){

};

void PackageBuilder::addFile(String sourceFile, String destName){
	PackageFileInformation fi;	
	fi.path = sourceFile;

	String shortName = sourceFile.split('/').back();

	if(destName.length() == 0){
		//just store in the root
		header.root.childFiles[shortName] = fi;
	}
	else{
		//store in the desired path, with the desired alias
		StringList stripped_path = destName.split("/");

		PackageNode* node = &header.root;

		for(unsigned int i = 0; i < stripped_path.size()-1; i++){
			std::map<String, PackageNode>::iterator it = node->children.find(stripped_path[i]);
			if(it == node->children.end()){
				//must create the directory

				PackageNode n;
				n.name = stripped_path[i];
				node->children[stripped_path[i]] = n;
				node = &node->children[stripped_path[i]];
			}
			else{
				node = &it->second;
			}
		}

		node->childFiles[stripped_path.back()] = fi;
	}	
};

void PackageBuilder::addDirectory(String directory){
	
};

bool PackageBuilder::createPackage(){
	if(packageName.length() == 0)return false;

	FileStream out(packageName, StreamMode::WriteOnly);
	if(!out.valid())return false;

	//prepare & save header
	header.save(&out);

	std::vector<PackageFileInformation> v;
	header.root.makeFileList(v);
	
	for(std::vector<PackageFileInformation>::iterator it = v.begin(); it != v.end(); it++){
		out.copy(it->path);
	}

	return true;
};

/************************************************************************/
/* Package Stream                                                       */
/************************************************************************/
PackageStream::PackageStream(){
	openStream = NULL;
};

PackageStream::PackageStream(String packageName){
	openStream = NULL;

	FileStream in(packageName, StreamMode::ReadOnly);

	if(in.valid()){
		header.load(&in);
	}

	this->packageName = packageName;
};

bool PackageStream::seekFile(String fileName){
	PackageFileInformation* fp = header.findFile(fileName);
	if(fp){
		openStream = new FileStream(packageName, StreamMode::ReadOnly);		
		openStream->seek(fp->begin);
		offset = (unsigned long)fp->begin;
		sizeConstraint = (unsigned long)fp->size;
		return true;
	}
	else return false;
};

void PackageStream::printFile(){
	const unsigned int k = sizeConstraint+1;
	char *buffer = new char[k];
	buffer[k-1] = '\0';
	openStream->read(buffer, sizeConstraint);
	std::cout << "printing file at "<<offset<<" sized "<<k<<": " << String(buffer, sizeConstraint) << std::endl;
	delete[] buffer;
};

void PackageStream::dumpFile(String destination){
	const unsigned int k = sizeConstraint;
	char *buffer = new char[k];
	openStream->read(buffer, sizeConstraint);
	FileStream a(destination, StreamMode::WriteOnly);
	fwrite(buffer, sizeof(char), sizeConstraint, a.handle());
	//cout << "printing file at "<<offset<<" sized "<<k<<": " << String(buffer, sizeConstraint) << endl;
	delete[] buffer;
};

void PackageStream::dumpPackageContents(){
	header.root.printContents();
};

void PackageStream::extractPackage(String where, bool keepOriginalPaths){
	if(!FileSystem::isDirectory(where)){
		FileSystem::makeDirectory(where);
	}

	if(FileSystem::isDirectory(where)){
		//extract
	}

};

/// sf::InputStream inherited
Int64 PackageStream::Read(char *data, Int64 byte_len){
	return openStream->read(data, byte_len);
};
/// sf::InputStream inherited
Int64 PackageStream::Seek(Int64 position){
	return openStream->seek(position);
};
/// sf::InputStream inherited
Int64 PackageStream::Tell(){
	return openStream->currentPosition() - offset;			
};
/// sf::InputStream inherited
Int64 PackageStream::GetSize(){
	return sizeConstraint;
};


NEPHILIM_NS_END

#endif