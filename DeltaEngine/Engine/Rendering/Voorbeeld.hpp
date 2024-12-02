#include <string>
#include <vector>
#include <map>

namespace Rendering
{
	struct Texture
	{

	};
}

namespace Temp
{
	struct Vector2 
	{ 
		float x;
		float y;
	};

	struct SpriteData
	{
		Rendering::Texture* sprite;
		Vector2 spriteStart;
		Vector2 spriteEnd;
	};

	// NOT FOR USER, ENGINE ONLY
	class TextureManager
	{
	public:
		~TextureManager()
		{
			// Delete all entries in map
			for (const auto& pair : _textures)
			{
				delete pair.second;
			}
		}

		void Add(const std::string& spritePath) 
		{ 
			Rendering::Texture* texture = 0x0;
			_textures.emplace(spritePath, texture);
		}

		Rendering::Texture* Get(const std::string& spritePath)
		{ 
			return _textures[spritePath];
		}

	private:
		std::map<std::string, Rendering::Texture*> _textures{};
	};

	class ResourceManager
	{
	public:
		void Add(const std::string& name, SpriteData spriteData)
		{
			_sprites.emplace(name, spriteData);
		}

		SpriteData* Get(const std::string& name)
		{
			return _sprites[name];
		}

	private:
		std::map<std::string, SpriteData*> _sprites;
	};

	struct TilemapEntry // DTO
	{
		std::string spriteName;
		std::string spritePath;
		Vector2 spriteStart;
		Vector2 spriteEnd;
	};

	TextureManager texturesManager{};
	ResourceManager resourcesManager{};

	class SpriteMap
	{
	public:
		SpriteMap(const std::string& name, std::vector<TilemapEntry> sprites)
			: _name{ name }
		{
			// Convert TilemapEntry DTO into SpriteData
			for (TilemapEntry& entry : sprites)
			{
				SpriteData spriteData
				{
					texturesManager.Get(entry.spritePath),
					entry.spriteStart,
					entry.spriteEnd
				};
				resourcesManager.Add(entry.spriteName, spriteData);
			}
		}

		SpriteData* Get(const std::string& spriteName)
		{
			return resourcesManager.Get(spriteName);
		}

	private:
		std::string _name;
	};

	class Sprite
	{
	public:
		Sprite(std::string spriteName) 
			: _sprite{ spriteName }
		{
			_spriteData = resourcesManager.Get(spriteName);
		}

		void SetSprite(std::string spriteName)
		{
			_sprite = spriteName;
			_spriteData = resourcesManager.Get(spriteName);
		}

	private:
		std::string _sprite;
		SpriteData* _spriteData;
	};

	// 1. Maak maps
	SpriteMap floormap
	{
		// 64x64 met 4 sprites
		"floor_map",
		{
			{
				"water",
				"Assets\\Texturs\\floor_map.png",
				{ 0.0f, 0.0f },
				{ 32.0f, 32.0f }
			},
			{
				"lava",
				"Assets\\Texturs\\floor_map.png",
				{ 32.0f, 0.0f }, 
				{ 64.0f, 32.0f }
			},
			{
				"grass",
				"Assets\\Texturs\\floor_map.png",
				{ 0.0f, 32.0f }, 
				{ 32.0f, 64.0f }
			},
			{
				"stone",
				"Assets\\Texturs\\floor_map.png",
				{ 32.0f, 32.0f }, 
				{ 64.0f, 64.0f }
			},
		}
	};

	// 2. 
	// AddComponent<Srite>("grass");
}