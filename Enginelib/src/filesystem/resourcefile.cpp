#include "resourcefile.hpp"
#include "../basics/logging.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class Secrets
{
	public:
	Secrets(SDL_RWops * file): m_file(file){}
	SDL_RWops * m_file;
};

ResourceFile::ResourceFile(void* data, uint size):
	m_secrets(std::make_unique<Secrets>(SDL_RWFromConstMem(data, size))),
	m_size(size)
{
	Logging::log(std::stringstream() << "Created ResourceFile of size " << size, Logging::TRACE);
	ASSERT(m_secrets->m_file, "Resource file failed to load, SDL_Error: " + std::string(SDL_GetError()));
}

ResourceFile::~ResourceFile() {
	Logging::log(std::stringstream() << "Destroying Resourcefile ", Logging::TRACE);
	if (!m_is_font) {
		ASSERT(m_secrets->m_file, "Resource file should not be null");
		SDL_RWclose(m_secrets->m_file);
	}
}

uint ResourceFile::get_size() {
	return m_size;
}

void * ResourceFile::get_font(int size) {
	ASSERT(m_secrets->m_file, "file is null");
	m_is_font = true;

	/*
	Bug in SDL - Must free memory here
	calling SDL_RWclose will result in
	segmentation fault when reading the font
	*/
	const int free_memory_please = 1;
	TTF_Font * out = TTF_OpenFontRW(m_secrets->m_file, free_memory_please, size);
	ASSERT(out, "Could not parse file as font " + std::string(TTF_GetError()));
	return out;
}

void * ResourceFile::get_surface() {
	ASSERT(m_secrets->m_file, "file is null");
	const int do_not_clear_source = 0;
	SDL_Surface * out = IMG_Load_RW(m_secrets->m_file, do_not_clear_source);
	ASSERT(out, "Could not parse file as surface " + std::string(SDL_GetError()));
	return out;
}

std::string ResourceFile::get_text() {
	ASSERT(m_secrets->m_file, "file is null");
	char * buf = new char[m_size];
	int objects = 1; //It's a single object
	size_t result = SDL_RWread(m_secrets->m_file, buf, m_size, objects);
	ASSERT(result != 0, "Could parse file as text " + std::string(SDL_GetError()));
	std::string text(buf);
	delete buf;
	return text;
}
