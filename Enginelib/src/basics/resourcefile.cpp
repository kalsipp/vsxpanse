#include "resourcefile.hpp"

ResourceFile::ResourceFile(void* data, uint size):
	m_file_p(SDL_RWFromConstMem(data, size)),
	m_size(size)
{
}

ResourceFile::~ResourceFile() {
	if (!m_is_font) {
		ASSERT(m_file_p != nullptr, "resourcefile should not be null");
		SDL_RWclose(m_file_p);
	}
}

SDL_RWops * ResourceFile::get_sdl_rwops() {
	return m_file_p;
}
uint ResourceFile::get_size() {
	return m_size;
}

TTF_Font * ResourceFile::get_font(int size) {
	ASSERT(m_file_p, "file is null");
	m_is_font = true;
	/*
	Bug in SDL - Must free memory here
	calling SDL_RWclose will result in
	segmetationfault when reading the font
	*/
	int free_memory_please = 1;
	return TTF_OpenFontRW(m_file_p, free_memory_please, size);
}

SDL_Surface * ResourceFile::get_surface() {
	ASSERT(m_file_p, "file is null");
	return IMG_Load_RW(m_file_p, 0);
}

std::string ResourceFile::get_text() {
	ASSERT(m_file_p, "file is null");
	char * buf = new char[m_size];
	int maxnum = 1; //I don't know what this is
	int result = SDL_RWread(m_file_p, buf, sizeof (buf), maxnum);
	ASSERT(result != 0, "Could not read file " + std::string(SDL_GetError()));
	std::string text(buf);
	delete buf;
	return text;
}
