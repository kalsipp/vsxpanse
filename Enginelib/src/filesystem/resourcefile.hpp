#pragma once
#include <iostream>
#include <string>
#include "../basics/helpers.hpp"

/*-------------------------------------------------------
	Contains the reference to one file-buffer
---------------------------------------------------------*/

class Secrets;
class ResourceFile{
	public:
		ResourceFile(void* data, uint size);
		~ResourceFile();
		ResourceFile(const ResourceFile &) = delete;
		ResourceFile & operator=(const ResourceFile &) = delete;
		std::string get_text();
		
		/* is TTF_Font * */
		void* get_font(int size);

		/* is SDL_Surface * */
		void * get_surface();
		uint get_size();
	private:
		std::unique_ptr<Secrets> m_secrets;
		// SDL_RWops * m_file_p = nullptr;
		const uint m_size;

		/* Need to keep track if it's a font to handle memory clearing properly */
		bool m_is_font = false;
};