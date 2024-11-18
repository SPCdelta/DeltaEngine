#include "Text.hpp"

ui::Text::Text(std::string text, std::string path, int size, int x, int y, Rendering::Color color, Rendering::Renderer* renderer)
	: _text{text}, _size{size}, _x{x}, _y{y}, _color{color}, _renderer{renderer}
{
	_font = Font::OpenFont(path.c_str(), size);

	if (_font == nullptr)
	{
		std::cerr << "Error loading font: " << Font::GetError() << std::endl;
	}
}

ui::Text::~Text() {
	unloadText();
}

void ui::Text::renderText() {
	
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
		return;
	}

	Rendering::Rect dstRect = {100, 100, 100, 100};

	Rendering::RenderCopy(_renderer, texture, nullptr, &dstRect);

	std::cout << dstRect.x << std::endl;

	//Rendering::FreeSurface(surface);
	//Rendering::DestroyTexture(texture);

}

void ui::Text::unloadText() {
	if (_font != nullptr) {
		Font::CloseFont(_font);
		_font == nullptr;
		//Font::QuitTTF();
	}
}
