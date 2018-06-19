#include "zipwrap.h"
#include "UnzipArchive.h"
#include "helpers.hpp"
using namespace ZipWrap;

void * GetFileFromZip(const std::string & zipPath,
	const std::string & filePath) 
{
	CZipArchive zip;

	size_t retarded_name_size = zipPath.size() > filePath.size() ? zipPath.size() : filePath.size();
	TCHAR *retarded_name = new TCHAR[retarded_name_size + 1];
	retarded_name[zipPath.size()] = 0;
	std::copy(zipPath.begin(), zipPath.end(), retarded_name);
	
	zip.Open(retarded_name);
	ASSERT(zip.IsOpen());
	
	CZipFile file;

	retarded_name[filePath.size()] = 0;
	std::copy(filePath.begin(), filePath.end(), retarded_name);
	
	bool success = zip.GetFile(retarded_name, &file);
	delete retarded_name;
	ASSERT(success);
	DWORD dwSize = file.GetSize();
	char * buff = new char[dwSize];
	file.Read(buff, dwSize);
	return buff;
}
