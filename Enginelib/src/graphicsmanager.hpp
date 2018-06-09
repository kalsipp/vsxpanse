#pragma once


#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "resourcemanager.hpp"
#include "basics/vector2d.hpp"
#include "basics/rect.hpp"
#include "basics/sprite.hpp"
#include "basics/helpers.hpp"
#include "basics/logging.hpp"


class GraphicsManager {
public:
	static void initialize();
	static void teardown();
	static void prepare_rendering();
	static void render_texture(const Sprite &,
	                           const Vector2D & pos,
	                           const Vector2D & scale,
	                           const double angle,
	                           bool centered,
	                           const SDL_RendererFlip flip);
	static void execute_rendering();
	static void load_texture(const std::string & path);
	static SDL_Texture * get_texture(const std::string & filename);
	static SDL_Texture * get_texture_from_text(const std::string &, TTF_Font*, SDL_Color&);
private:
	// static SDL_Surface * load_surface_from_sdl_rwops(SDL_RWops*);
	static SDL_Surface * load_image_to_surface(const std::string & path);
	static SDL_Texture * convert_surface_to_texture(SDL_Surface*);
	GraphicsManager();
	static bool m_initialized;
	static std::map<std::string, SDL_Texture*> m_textures;
	static std::map<std::string, TTF_Font> m_fonts;
	static SDL_Window * m_main_window;
	static SDL_Surface * m_main_surface;
	static SDL_Renderer * m_main_renderer;
	static SDL_Color render_draw_color;
	static unsigned int m_screen_width;
	static unsigned int m_screen_height;
	static std::string m_window_name;
};