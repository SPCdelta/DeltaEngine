#include "FontManager.hpp"

FontManager FontManager::instance;

FontManager& FontManager::get_instance()
{
	return instance;
}

FontManager::FontManager() 
{

}

FontManager::~FontManager()
{ 
    _fonts.clear();
    TTF_Quit();
}

void FontManager::AddFont(const std::string& fontName, const std::string& path)
{
	instance._fontLookup.emplace(fontName, path);
}

std::shared_ptr<FontWrapper> FontManager::Get(const std::string& fontName, int fontSize)
{
	return AddInternalFont(fontName, fontSize);
}

void FontManager::Cleanup() 
{

}

std::shared_ptr<FontWrapper> FontManager::AddInternalFont(const std::string& name, int size)
{
	if (!instance._fontLookup.contains(name))
		throw std::exception("Font does not exist");

	// If no sizes are in map, create map
	if (instance._fonts.contains(name))
		instance._fonts[name] = {};

	std::unordered_map<int, std::shared_ptr<FontWrapper>>& fontFontSizes = instance._fonts[name];
	if (!HasFontSize(fontFontSizes, size))
		fontFontSizes.emplace(size, std::make_shared<FontWrapper>(Font::OpenFont(instance._fontLookup[name], size)));
	return fontFontSizes[size];
}

bool FontManager::HasFontSize(const std::unordered_map<int, std::shared_ptr<FontWrapper>>& fontFontSizes, int size)
{
	return (fontFontSizes.find(size) != fontFontSizes.end());
}
