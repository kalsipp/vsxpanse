#include "FileHandler.hpp"

bool FileHandler::m_initialized;
ResourceArchive * FileHandler::m_archive = nullptr;


void FileHandler::initialize(const std::string & path)
{
	ASSERT(m_initialized == false, "You're trying to initialize FileHandler twice");
	m_initialized = true;
	m_archive = new ResourceArchive(path);
}

ResourceFile * FileHandler::get_item(const std::string & path)
{
	ASSERT(m_initialized, "You need to initialize FileHandler first");
	return m_archive->get_item(path);
}
