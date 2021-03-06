#include "pch.h"
#include <fstream>
#include <windows.h>

#include "filesystem/zipwrap.hpp"
#include "filesystem/resourcearchive.hpp"



TEST(resourcearchive, constructor_test)
{
	ResourceArchive archive("TestResources");
}
TEST(resourcearchive, get_item_test)
{
	ResourceArchive archive("TestResources");
	std::string path_to_file = "Fonts\\calibri.ttf";
	ResourceFile * file = archive.get_item(path_to_file);
	ASSERT_NE(file, nullptr);
}
TEST(resourcearchive, free_item_test)
{
	ResourceArchive archive("TestResources");
	std::string path_to_file = "Fonts\\calibri.ttf";
	ResourceFile * file;
	for (int i = 0; i < 5; ++i)
	{
		file = archive.get_item(path_to_file);
		archive.free_item(path_to_file);
	}

}
