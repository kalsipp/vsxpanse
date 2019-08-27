#include "pch.h"

#include <fstream>
#include <windows.h>

#include "filesystem/zipwrap.hpp"
#define private public
#include "filesystem/resourcearchive.hpp"
#include "filesystem/resourcefile.hpp"

TEST(Constructor_noargs, test)
{
	char buff[100];
	ResourceFile rs_file(buff, 100);
	ASSERT_TRUE(rs_file.m_size == 100);
	ASSERT_TRUE(rs_file.m_file_p != nullptr);
}
TEST(get_sdl_rwops_test, test)
{
	char buff[100];
	ResourceFile rs_file(buff, 100);
	ASSERT_TRUE(rs_file.get_sdl_rwops() == rs_file.m_file_p);
}
TEST(get_size_test, test)
{
	char buff[100];
	ResourceFile rs_file(buff, 100);
	ASSERT_TRUE(rs_file.get_size() == rs_file.m_size);
}
		
TEST(get_font_test, test)
{
	TTF_Init();
	ResourceArchive archive("TestResources");
	std::string path_to_file = "Fonts\\calibri.ttf";
	ResourceFile * file = archive.get_item(path_to_file);
	TTF_Font * font = file->get_font(16);
	ASSERT_NE(font, nullptr);
	archive.free_item(path_to_file);
}
TEST(get_surface_test, test)
{
	ResourceArchive archive("TestResources");
	std::string path_to_file = "Images\\19.jpg";
	ResourceFile * file = archive.get_item(path_to_file);
	SDL_Surface * surf = file->get_surface();
	ASSERT_NE(surf, nullptr);
}
TEST(get_text_test, test)
{
	char buff[10] = "abcdefghi";
	ResourceFile rs_file(buff, 10);
	std::string buff_g = rs_file.get_text();
	for (int byte = 0; byte < 10; ++byte)
	{
		ASSERT_TRUE(buff_g[byte] == buff[byte]);
	}
}
