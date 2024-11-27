#include "Text.hpp"

using namespace Ui;

Text::Text(const std::string& text, const std::string& path, const int size, const int x, const int y, const Rendering::Color& color)
	: _text{text}, _size{size}, _x{x}, _y{y}, _color{color}
{
	_font = Font::OpenFont(path.c_str(), size);

	if (_font == nullptr)
	{
		std::cerr << "Error loading font: " << Font::GetError() << std::endl;
	}
}

Text::~Text()
{
	unloadText();
}

void Text::Render()
{
	
	if (_font == nullptr)
	{
		std::cerr << "Font not loaded" << std::endl;
		//Font::QuitTTF();
		return;
	}

	Rendering::Surface* surface = Font::RenderText_Solid(_font, _text.c_str(), _color);

	if (surface == nullptr) {
		std::cerr << "Error creating surface: " << Rendering::GetError() << std::endl;

		Font::CloseFont(_font);
		//Font::QuitTTF();
		return;
	}

	Rendering::Texture* texture = Rendering::CreateTextureFromSurface(_renderer, surface);

	if (texture == nullptr) {
		std::cerr << "Error creating texture: " << Rendering::GetError() << std::endl;
		Rendering::FreeSurface(surface);
		Rendering::DestroyTexture(texture);
		return;
	}

	Rendering::Rect dstRect = {_x, _y , surface->w, surface->h};

	Rendering::RenderCopy(_renderer, texture, nullptr, &dstRect);


	//Rendering::FreeSurface(surface);
	//Rendering::DestroyTexture(texture);

}

void Text::unloadText()
{
	if (_font != nullptr) {
		Font::CloseFont(_font);
		_font == nullptr;
		//Font::QuitTTF();
	}
}
