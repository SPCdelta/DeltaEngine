#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "../UI/FontWrapper.hpp"

class FontManager
{
public:
	static FontManager& get_instance();

	FontManager(const FontManager&) = delete;
	FontManager(FontManager&&) = delete;
	FontManager& operator=(const FontManager&) = delete;
	FontManager& operator=(FontManager&&) = delete;

	static void AddFont(const std::string& fontName, const std::string& path);
	static std::shared_ptr<FontWrapper> Get(const std::string& fontName, int fontSize);

	static void Cleanup();

private:
	static FontManager instance;
	std::unordered_map<std::string, std::string> _fontLookup; // Name to path
	std::unordered_map<std::string, std::unordered_map<int, std::shared_ptr<FontWrapper>>> _fonts; // Name to pair of size to font

	static std::shared_ptr<FontWrapper> AddInternalFont(const std::string& name, int size);

	static bool HasFontSize(const std::unordered_map<int, std::shared_ptr<FontWrapper>>& fontFontSizes, int size);

	FontManager();
	~FontManager();
};