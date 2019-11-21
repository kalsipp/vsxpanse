#pragma once

#include <map>
#include "basics/vector2d.hpp"
#include "basics/sprite.hpp"
#include "filesystem/resourcefile.hpp"
#include <memory>
/*-------------------------------------------------------
	Interface for presenting images to the screen.
	Owns prepared textures, loaded from files.
	Users simply asks to present it.
---------------------------------------------------------*/
class Secrets;
struct SDL_Texture;
struct SDL_Surface;
class RectInt;
class GraphicsManager
{
public:
	static void initialize();
	static void teardown();
	static void prepare_rendering();
	static void render_texture(const Sprite &,
							   const Vector2D &pos,
							   const Vector2D &scale,
							   const double angle,
							   bool centered);
	static void draw_circle(const Vector2D &pos, int radius);
	static void draw_point(const Vector2D &pos);
	static void draw_line(const Vector2D &from, const Vector2D &to);
	static void execute_rendering();
	static std::unique_ptr<Sprite> load_sprite(ResourceFile *file);
	static std::unique_ptr<Sprite> get_sprite_from_text(const std::string &, void *, RectInt &);
	static void set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	static void destroy_texture(SDL_Texture *text);
	/*-------------------------------------------------------
		Converts the surface to an SDL_Texture.
		Note that GraphicsManager does not own the returned
		texture and it must be freed accordingly.
	---------------------------------------------------------
	@param surf - The surface to convert to a texture.
	@return - pointer to the created texture.
	---------------------------------------------------------*/
	static SDL_Texture *convert_surface_to_texture(SDL_Surface *surf);
	static constexpr unsigned int get_screen_height() { return m_screen_height; }
	static constexpr unsigned int get_screen_width() { return m_screen_width; }

private:
	// static SDL_Surface * load_surface_from_sdl_rwops(SDL_RWops*);
	static SDL_Surface *load_image_to_surface(const std::string &path);
	GraphicsManager();
	static bool m_initialized;
	static std::unique_ptr<Secrets> m_internals;
	static unsigned int m_screen_width;
	static unsigned int m_screen_height;
	static std::string m_window_name;
};