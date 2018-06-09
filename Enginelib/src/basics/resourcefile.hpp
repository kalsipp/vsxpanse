#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "helpers.hpp"

class ResourceFile{
	public:
		ResourceFile(void* data, uint size);
		~ResourceFile();
		ResourceFile(const ResourceFile &) = delete;
		ResourceFile & operator=(const ResourceFile &) = delete;
		SDL_RWops * get_sdl_rwops();
		std::string get_text();
		TTF_Font * get_font(int size);
		SDL_Surface * get_surface();
		uint get_size();
	private:
		SDL_RWops * m_file_p = nullptr;
		const uint m_size;
		bool m_is_font = false;
};