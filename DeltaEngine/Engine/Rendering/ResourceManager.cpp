#include "ResourceManager.hpp"

ResourceManager ResourceManager::instance;

ResourceManager& ResourceManager::get_instance()
{
	return instance;
}

ResourceManager::ResourceManager() 
{

}

ResourceManager::~ResourceManager()
{
	// Delete all entries in map
	for (const auto& pairsprite : _sprites)
		delete pairsprite.second;
}

void ResourceManager::AddFont(const std::string& fontName, const std::string& fontPath)
{
	FontManager::AddFont(fontName, fontPath);
}

std::shared_ptr<FontWrapper> ResourceManager::GetFont(const std::string& name, int fontSize)
{
	return FontManager::Get(name, fontSize);
}

void ResourceManager::AddSprite(const std::string& name, const std::string& spritePath, const std::string& category)
{
	Rendering::Texture* texture = TextureManager::Add(spritePath);

	int width = 0;
	int height = 0;

	Rendering::QueryTexture(texture, nullptr, nullptr, &width, &height);
	std::string category_ = category.empty() ? name : category;

	SpriteData* spriteData = new SpriteData
	(
		texture,
		{ 0.0f, 0.0f },
		{ static_cast<float>(width), static_cast<float>(height) },
		category_
	);

	AddSprite(name, spriteData);
}

SpriteData* ResourceManager::Get(const std::string& name)
{
	if (!instance._sprites.contains(name))
		assert(std::string{"Sprite does not exist!!"}.empty());
	return instance._sprites[name];
}

std::unordered_map<std::string, SpriteData*>& ResourceManager::GetAllSprites()
{
	return instance._sprites;
}

std::unordered_map<std::string, SpriteData*> ResourceManager::GetSprites(std::vector<std::string> categories)
{
	std::unordered_map<std::string, SpriteData*> result;
	for (const auto& pair : instance._sprites) 
	{
		if (pair.second && std::find(categories.begin(), categories.end(), pair.second->category) != categories.end() ) 
			result[pair.first] = pair.second;
	}
	return result;
}

void ResourceManager::AddAudio(const std::string& name, const std::string& path)
{
	instance._audio[name] = path;
}

const std::string& ResourceManager::GetAudio(const std::string& name)
{
	return instance._audio[name];
}

void ResourceManager::Cleanup()
{
	TextureManager::Cleanup();
	FontManager::Cleanup();
}

void ResourceManager::AddSprite(const std::string& name, SpriteData* spriteData)
{
	instance._sprites.emplace(name, spriteData);
}