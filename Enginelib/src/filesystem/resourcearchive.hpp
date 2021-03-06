#pragma once
#include <string>
#include <map>
#include "resourcefile.hpp"

//#define RESOURCE_USING_ZIP
#ifdef RESOURCE_USING_ZIP
#include "basics/zipwrap.hpp"
#endif // RESOURCE_USING_ZIP


/*-------------------------------------------------------
Class to abstract access to the file system.
This represents one folder/zip file alike.
Only supports files smaller than 4GB.
---------------------------------------------------------*/
class ResourceArchive {
public:
	
	/*-------------------------------------------------------
	@param path, path to archive
	---------------------------------------------------------*/
	ResourceArchive(const std::string & path);
	
	/*-------------------------------------------------------
	Get item from file system
	---------------------------------------------------------
	@param name, relative path to item
	@param stored_in_archive, will keep a copy of the file in for faster loading the next times.
						 Set to false for large files.
	@return Pointer to ResourceFile
	---------------------------------------------------------*/
	ResourceFile * get_item(const std::string & name);
	
	/*-------------------------------------------------------
	Free resource item based on path.
	All pointers to that item will no longer be valid. 
	---------------------------------------------------------
	@param name, relative path to item
	---------------------------------------------------------*/
	void free_item(const std::string & name);

private:
	void read_file(const std::string & path, void ** buffer, size_t* size);
	std::map<std::string, ResourceFile *> m_files;
	std::string m_source_path;
#ifdef RESOURCE_USING_ZIP
	ZipWrap m_zip_archive;
	ZipWrap m_engine_zip_archive;
#endif //RESOURCE_USING_ZIP
};