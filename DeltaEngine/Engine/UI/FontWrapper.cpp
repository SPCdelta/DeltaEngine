#include "FontWrapper.hpp"

FontWrapper::FontWrapper(Font::Font* font) 
	: _font{font} 
{

}

FontWrapper ::~FontWrapper()
{
	Font::CloseFont(_font);
}

Font::Font* FontWrapper::GetFont() const
{
	return _font;
}

