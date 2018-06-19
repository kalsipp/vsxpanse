#pragma once
#include <string>
#include "UnzipArchive.h"

class ZipWrap
{
public:
	/*-------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------*/
	ZipWrap() {}

	/*-------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------*/
	ZipWrap(const std::string & path);

	/*-------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------*/
	~ZipWrap();

	/*-------------------------------------------------------
	Gets a pointer to the contents of a file from a zip
	---------------------------------------------------------
	Not necessarily the fastest file opener in the land.

	@param zipPath, path to the zip-file
	@param filePath, path to the file within the zip
	@return pointer to the file contents. Clear contents by calling
			clear_zip_entry
	---------------------------------------------------------*/
	void get_entry_from_zip(const std::string & filePath, void ** filecont, size_t * size);

	/*-------------------------------------------------------
	Cleans the zip
	---------------------------------------------------------
	@param file, pointer to the file
	---------------------------------------------------------*/
	void clear_zip_entry(void * file);

private:
	CZipArchive m_zip_archive;

};