#include "gridbackground.hpp"
#include "graphicsmanager.hpp"
#include "engine.hpp"
#include "basics/helpers.hpp"
#include "components/spritecomponent.hpp"

MapTile::MapTile(const MapTileSprite sprite) :m_sprite(sprite) {}

const std::string MapTile::MapTilePaths[SIZEOF_MAPTILESPRITE] = {
	"Images\\ground.png",
	"Images\\grass.png"
};

void GridBackground::initialize(ResourceArchive * archive)
{
	m_size = GridMap::get_size();
	generate_surface(archive);
}

void GridBackground::render()
{
	int posses[GRIBACKGROUND_NUMBER_OF_PARTS_X];
	for (int i = 0; i < GRIBACKGROUND_NUMBER_OF_PARTS_X; ++i)
	{
		posses[i] = i * SDL_SURFACE_MAX_SIZE;
	}
	
	for (int y = 0; y < GRIBACKGROUND_NUMBER_OF_PARTS_X; ++y)
	{
		for (int x = 0; x < GRIBACKGROUND_NUMBER_OF_PARTS_X; ++x)
		{
			Vector2D pos(posses[x], posses[y]);
			const int indx = x + GRIBACKGROUND_NUMBER_OF_PARTS_X * y;
			GraphicsManager::render_texture(*m_map_sprites[indx], pos, Vector2D(1, 1), 0, true, SDL_FLIP_NONE);
		}
	}
}

void GridBackground::teardown()
{
	for (int part = 0; part = GRIBACKGROUND_NUMBER_OF_PARTS; ++part)
	{
		delete m_map_sprites[part];
		SDL_DestroyTexture(m_textures[part]);
	}
}

void GridBackground::generate_surface(ResourceArchive * archive)
{

	struct tmp{
		static void generate_texture(SDL_Texture ** container, const Vector2DInt &  size, SDL_Surface * surfs[])
		{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			const Uint32 rmask = 0xff000000;
			const Uint32 gmask = 0x00ff0000;
			const Uint32 bmask = 0x0000ff00;
			const Uint32 amask = 0x000000ff;
#else
			const Uint32 rmask = 0x000000ff;
			const Uint32 gmask = 0x0000ff00;
			const Uint32 bmask = 0x00ff0000;
			const Uint32 amask = 0xff000000;
#endif
			const int some_depth_format_number_idk = 32;
			SDL_Surface * map_surf = SDL_CreateRGBSurface(NULL, SDL_SURFACE_MAX_SIZE, SDL_SURFACE_MAX_SIZE, some_depth_format_number_idk, rmask, gmask, bmask, amask);
			ASSERT(map_surf != 0, "Could not create surface, SDL_Error: " + std::string(SDL_GetError()));
			for (int y = 0; y < size.y; ++y)
			{
				for (int x = 0; x < size.x; ++x)
				{
					const int sprite = helpers::random_int(0, MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE - 1);
					SDL_Surface * surf = surfs[sprite];
					SDL_Rect pos = { x*GRIDTILESIZE, y*GRIDTILESIZE, GRIDTILESIZE, GRIDTILESIZE };
					SDL_BlitSurface(surf, NULL, map_surf, &pos);
				}
			}

			*container = GraphicsManager::convert_surface_to_texture(map_surf);
			SDL_FreeSurface(map_surf);
			
		}
	};


	if (!MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE)
	{
		Logging::log("SIZEOF_MAPTILESPRITE is 0", Logging::WARNING);
		return;
	}

	/* Prepare all surfaces that we're gonna use */
	SDL_Surface * surfs[MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE];
	for (int i = 0; i < MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE; ++i)
	{
		surfs[i] = archive->get_item(MapTile::MapTilePaths[i])->get_surface();
	}

	const int sprite_width = surfs[0]->w;
	const int sprite_height = surfs[0]->h;
	/* A surface may max be 8192x8192 large, so that's what we're gonna use*/

	for (int part = 0; part < GRIBACKGROUND_NUMBER_OF_PARTS; ++part)
	{
		tmp::generate_texture(&m_textures[part], m_size, surfs);
		m_map_sprites[part] = new Sprite(m_textures[part]);
	}
}

