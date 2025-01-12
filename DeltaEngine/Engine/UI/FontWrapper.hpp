#pragma once

#include "Font.hpp"

class FontWrapper
{
public:
	FontWrapper(Font::Font* font);
	~FontWrapper();

	Font::Font* GetFont() const;

private:
	Font::Font* _font;
};

namespace Font
{
	inline const Math::Vector2 GetFontSize(std::shared_ptr<FontWrapper> font, const std::string& text)
	{
		std::unique_ptr<int> w = std::make_unique<int>();
		std::unique_ptr<int> h = std::make_unique<int>();
		TTF_SizeText(font->GetFont(), text.c_str(), w.get(), h.get());
		return Math::Vector2{*w, *h};
	}
}