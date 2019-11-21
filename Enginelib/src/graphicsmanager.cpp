#include "graphicsmanager.hpp"
#include "basics/logging.hpp"
#include "filesystem/resourcearchive.hpp"
#include "basics/helpers.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Secrets
{
public:
	SDL_Window *m_main_window = nullptr;
	SDL_Surface *m_main_surface = nullptr;
	SDL_Renderer *m_main_renderer = nullptr;
	std::map<ResourceFile *, SDL_Texture *> m_textures;
};

/* Parameters */

bool GraphicsManager::m_initialized = false;
// SDL_Window * GraphicsManager::m_main_window = nullptr;
// SDL_Surface * GraphicsManager::m_main_surface = nullptr;
// SDL_Renderer * GraphicsManager::m_main_renderer = nullptr;
unsigned int GraphicsManager::m_screen_width = 1024;
unsigned int GraphicsManager::m_screen_height = 768;
// std::map<ResourceFile *, SDL_Texture*> GraphicsManager::m_textures;
std::string GraphicsManager::m_window_name = "Let's go bois";
std::unique_ptr<Secrets> GraphicsManager::m_internals{nullptr};
/* Public Routines */

void GraphicsManager::initialize()
{
	m_internals = std::make_unique<Secrets>();
	ASSERT(!GraphicsManager::m_initialized, "You cannot initialize GraphicsManager twice!");
	int ok = SDL_Init(SDL_INIT_VIDEO);
	ASSERT(ok >= 0,
		   "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) // 0 = nearest pixel sampling
	{
		Logging::log(std::stringstream() << "Warning: Linear texture filtering not enabled!", Logging::WARNING);
	}
	GraphicsManager::m_internals->m_main_window = SDL_CreateWindow(
		GraphicsManager::m_window_name.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_screen_width,
		m_screen_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	ASSERT(GraphicsManager::m_internals->m_main_window != NULL,
		   "Window could not be created! SDL_Error:" + std::string(SDL_GetError()));

	GraphicsManager::m_internals->m_main_renderer = SDL_CreateRenderer(
		GraphicsManager::m_internals->m_main_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	ASSERT(GraphicsManager::m_internals->m_main_renderer != NULL,
		   "Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));

	GraphicsManager::m_internals->m_main_surface = SDL_GetWindowSurface(GraphicsManager::m_internals->m_main_window);

	ASSERT(GraphicsManager::m_internals->m_main_surface != NULL,
		   "Surface could not be created! SDL Error: " + std::string(SDL_GetError()));

	SDL_SetRenderDrawColor(GraphicsManager::m_internals->m_main_renderer, 0x0, 0x0, 0x0, 0x0);

	int img_flags = IMG_INIT_PNG;
	ok = IMG_Init(img_flags) & img_flags;

	ASSERT(ok,
		   "SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));

	ok = TTF_Init();
	ASSERT(ok != -1,
		   "SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
	GraphicsManager::m_initialized = true;
	Logging::log("Finished initialing GraphicsManager");
}

void GraphicsManager::teardown()
{
	for (auto i = GraphicsManager::m_internals->m_textures.begin(); i != GraphicsManager::m_internals->m_textures.end(); ++i)
	{
		SDL_DestroyTexture((*i).second);
	}
	SDL_DestroyRenderer(GraphicsManager::m_internals->m_main_renderer);
	SDL_FreeSurface(GraphicsManager::m_internals->m_main_surface);
	SDL_DestroyWindow(GraphicsManager::m_internals->m_main_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	m_initialized = false;
	Logging::log("Finished teardown GraphicsManager");
}

void GraphicsManager::prepare_rendering()
{
	set_render_draw_color(0, 0, 0, 0);
	SDL_RenderClear(GraphicsManager::m_internals->m_main_renderer);
}

void GraphicsManager::render_texture(const Sprite &sprite,
									 const Vector2D &pos,
									 const Vector2D &scale,
									 const double angle,
									 bool centered)
{
	SDL_Texture *texture = sprite.get_sdl_texture();
	ASSERT(texture != nullptr, "Trying to render null texture");
	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	double posx = 0;
	double posy = 0;
	double scalex = sprite.get_rect().h * scale.x;
	double scaley = sprite.get_rect().w * scale.y;
	if (centered)
	{
		posx = round(pos.x - scalex / 2);
		posy = round(pos.y - scaley / 2);
	}
	else
	{
		posx = round(pos.x);
		posy = round(pos.y);
	}
	SDL_Rect dstrect = {int(round(posx)),
						int(round(posy)),
						int(round(scalex)),
						int(round(scaley))};
	SDL_Rect srcrect = {
		sprite.get_rect().x,
		sprite.get_rect().y,
		sprite.get_rect().w,
		sprite.get_rect().h};
	SDL_RenderCopyEx(
		GraphicsManager::m_internals->m_main_renderer, // SDL_Renderer*          renderer
		texture,									   // SDL_Texture*           texture
		&srcrect,									   // const SDL_Rect*        srcrect. selects a subpart of the texture.
		&dstrect,									   // const SDL_Rect*        dstrect
		angle,										   // const double           angle
		NULL,										   // const SDL_Point*       center
		SDL_FLIP_NONE);										   // const SDL_RendererFlip flip
}

void GraphicsManager::draw_circle(const Vector2D &pos, int radius)
{
	/* Stolen by https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl */
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int err = tx - (radius << 1); // shifting bits left by 1 effectively
								  // doubles the value. == tx - diameter
	int posx = helpers::round_to_int(pos.x);
	int posy = helpers::round_to_int(pos.y);
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx + x, posy - y);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx + x, posy + y);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx - x, posy - y);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx - x, posy + y);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx + y, posy - x);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx + y, posy + x);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx - y, posy - x);
		SDL_RenderDrawPoint(m_internals->m_main_renderer, posx - y, posy + x);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}

void GraphicsManager::draw_point(const Vector2D &pos)
{
	int x = helpers::round_to_int(pos.x);
	int y = helpers::round_to_int(pos.y);
	int success = SDL_RenderDrawPoint(m_internals->m_main_renderer, x, y);
	ASSERT(success == 0, SDL_GetError());
}

void GraphicsManager::draw_line(const Vector2D &from, const Vector2D &to)
{
	int from_x = (int)round(from.x);
	int from_y = (int)round(from.y);
	int to_x = (int)round(to.x);
	int to_y = (int)round(to.y);
	int success = SDL_RenderDrawLine(m_internals->m_main_renderer, from_x, from_y, to_x, to_y);
	ASSERT(success == 0, SDL_GetError());
}

void GraphicsManager::execute_rendering()
{
	SDL_RenderPresent(GraphicsManager::m_internals->m_main_renderer);
}

std::unique_ptr<Sprite> GraphicsManager::load_sprite(ResourceFile *file)
{
	if (!m_internals->m_textures.count(file))
	{
		Logging::log(std::stringstream() << "Loaded texture " << file);
		void *new_surf = file->get_surface();
		SDL_Texture *new_text = GraphicsManager::convert_surface_to_texture((SDL_Surface *)new_surf);
		m_internals->m_textures[file] = new_text;
	}
	auto newSprite = std::make_unique<Sprite>(m_internals->m_textures[file]);
	return newSprite;
}

std::unique_ptr<Sprite> GraphicsManager::get_sprite_from_text(const std::string &text, void *font, RectInt &textColor)
{
	SDL_Color color = {textColor.x, textColor.y, textColor.w, textColor.h};
	SDL_Surface *new_surf = TTF_RenderText_Solid((TTF_Font *)font, text.c_str(), color);
	SDL_Texture *new_text = convert_surface_to_texture(new_surf);

	SDL_FreeSurface(new_surf);
	return std::make_unique<Sprite>(new_text);
}

void GraphicsManager::set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(GraphicsManager::m_internals->m_main_renderer,
						   r,
						   g,
						   b,
						   a);
}

void GraphicsManager::destroy_texture(SDL_Texture *text)
{
	ASSERT(text != nullptr, "Trying to destroy nullptr");
	SDL_DestroyTexture(text);
}

/* Private routines */

SDL_Surface *GraphicsManager::load_image_to_surface(const std::string &filename)
{
	SDL_Surface *new_surf = IMG_Load(filename.c_str());
	ASSERT(new_surf, IMG_GetError());
	return new_surf;
}

SDL_Texture *GraphicsManager::convert_surface_to_texture(SDL_Surface *new_surf)
{
	SDL_Texture *out = SDL_CreateTextureFromSurface(GraphicsManager::m_internals->m_main_renderer, new_surf);
	ASSERT(out, "Could not load texture, SDL_Error: " + std::string(SDL_GetError()));
	return out;
}
