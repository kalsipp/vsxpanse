#pragma once
#include <string>
#include "filesystem/resourcearchive.hpp"
class FileHandler
{
public:
	static void initialize(const std::string & path);
	static ResourceFile * get_item(const std::string & path);
private:
	FileHandler() {}
	static bool m_initialized;
	static ResourceArchive * m_archive;
};

