#include "zipwrap.hpp"
#include "../basics/helpers.hpp"
#include "../basics/logging.hpp"
ZipWrap::ZipWrap(const std::string & path)
{
	ASSERT(m_zip_archive.IsOpen() == false, "You must close zip archive before opening it again");
	TCHAR * tmp_name = new TCHAR[path.size() + 1];
	tmp_name[path.size()] = 0; /* null termination */
	std::copy(path.begin(), path.end(), tmp_name);
	m_zip_archive.Open(tmp_name);
	ASSERT(m_zip_archive.IsOpen(), "Could not open zip archive " + path);
}

ZipWrap::~ZipWrap()
{
	m_zip_archive.Close();
}

void ZipWrap::get_entry_from_zip(const std::string & file_path, void ** filecont, size_t * size)
{
	ASSERT(m_zip_archive.IsOpen(), "You have to open the zip first");
	CZipFile file;
	TCHAR * tmp_name = new TCHAR[file_path.size() + 1];
	tmp_name[file_path.size()] = 0;
	std::copy(file_path.begin(), file_path.end(), tmp_name);
	bool success = m_zip_archive.GetFile(tmp_name, &file);
	ASSERT(success, "Could not open file " + file_path);
	delete tmp_name;
	DWORD dwSize = file.GetSize();
	*size = dwSize;
	*filecont = new char[dwSize];
	file.Read(*filecont, dwSize);
}

void ZipWrap::clear_zip_entry(void * file)
{
	ASSERT(file, "Trying to clear null zip-entry");
	delete file;
}