#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "../UI/Font.hpp"

class FontManager
{
public:
	static FontManager& get_instance() 
	{ 
		return instance; 
	}

	FontManager(const FontManager&) = delete;
	FontManager(FontManager&&) = delete;
	FontManager& operator=(const FontManager&) = delete;
	FontManager& operator=(FontManager&&) = delete;

	static void AddFont(const std::string& fontName, const std::string& path)
	{
		instance._fontLookup.emplace(fontName, path);
	}

	static Font::Font* Get(const std::string& fontName, int fontSize)
	{
		return AddInternalFont(fontName, fontSize);
	}

	static void Cleanup()
	{
		for (auto& sizes : instance._fonts)
		{
			for (auto& font : sizes.second)
			{
				Font::CloseFont(font.second);
			}
		}
	}

private:
	static FontManager instance;
	std::unordered_map<std::string, std::string> _fontLookup; // name to path
	std::unordered_map<std::string, std::unordered_map<int, Font::Font*>> _fonts; // name to pair of size to font

	static Font::Font* AddInternalFont(const std::string& name, int size)
	{
		if (!instance._fontLookup.contains(name))
		{
			throw std::exception("Font does not exist");
		}

		// If no sizes are in map, create map
		if (instance._fonts.contains(name))
		{
			instance._fonts[name] = {};
		}

		std::unordered_map<int, Font::Font*>& fontFontSizes = instance._fonts[name];
		if (!HasFontSize(fontFontSizes, size))
		{
			fontFontSizes.emplace(size, Font::OpenFont(instance._fontLookup[name], size));
		}

		return fontFontSizes[size];
	}

	static bool HasFontSize(const std::unordered_map<int, Font::Font*>& fontFontSizes, int size)
	{
		return (fontFontSizes.find(size) != fontFontSizes.end());
	}

	FontManager();
};