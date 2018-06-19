#include "gridbackground.hpp"
#include "graphicsmanager.hpp"
#include "engine.hpp"
#include "basics/helpers.hpp"
#include "components/spritecomponent.hpp"
void GridBackground::initialize(const Vector2DInt & size, ResourceArchive * archive)
{
	m_size = Vector2DInt(size);
	for (int x = 0; x < m_size.x; ++x)
	{
		for (int y = 0; y < m_size.y; ++y)
		{
			Vector2DInt pos(x, y);
			int x = helpers::random_int(0, MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE - 1);
			m_tiles[pos] = new MapTile(MapTile::MapTileSprite(x));
		}
	}
	generate_surface(archive);
}

void GridBackground::render()
{
	GraphicsManager::render_texture(*m_map_sprite, m_owner->transform().get_position(), Vector2D(1, 1), 0, true, SDL_FLIP_NONE);
}

void GridBackground::teardown()
{
	delete m_map_sprite;
	SDL_DestroyTexture(m_texture);
	for (auto it = m_tiles.begin(); it != m_tiles.end(); ++it)
	{
		delete it->second;
	}
}

void GridBackground::generate_surface(ResourceArchive * archive)
{
	if (!MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE)
	{
		Logging::log("SIZEOF_MAPTILESPRITE is 0", Logging::WARNING);
		return;
	}
	SDL_Surface * surfs[MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE];

	for (int i = 0; i < MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE; ++i)
	{
		surfs[i] = archive->get_item(MapTile::MapTilePaths[i])->get_surface();
	}
	const int sprite_width = surfs[0]->w;
	const int sprite_height = surfs[0]->h;
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

	SDL_Surface * map_surf = SDL_CreateRGBSurface(NULL, m_size.x*sprite_width, m_size.y*sprite_height, 32, rmask, gmask, bmask, amask);
	for (auto it = m_tiles.begin(); it != m_tiles.end(); ++it)
	{
		int sprite = it->second->m_sprite;
		SDL_Surface * surf = surfs[sprite];
		SDL_Rect pos = { it->first.x*sprite_width, it->first.y*sprite_height, sprite_width, sprite_height };
		SDL_BlitSurface(surf, NULL, map_surf, &pos);
	}
	m_texture = GraphicsManager::convert_surface_to_texture(map_surf);
	m_map_sprite = new Sprite(m_texture);
	SDL_FreeSurface(map_surf);
	for (int i = 0; i < MapTile::MapTileSprite::SIZEOF_MAPTILESPRITE; ++i)
	{
		SDL_FreeSurface(surfs[i]);
	}
}

