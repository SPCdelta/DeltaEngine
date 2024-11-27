#include "Text.hpp"

using namespace Ui;

Text::Text(const std::string& text, const std::string& path, const Rendering::Color& color) : Renderable{path.c_str()},
	  _text{text},
	  _color{color},
	  _path{path}
{
	_font = Font::OpenFont(path.c_str(), 0);
	if (_font == nullptr)
	{
		std::cerr << "Error loading font: " << Font::GetError() << std::endl;
	}
}

Text::Text(const Text& other)
	: Renderable{other._path.c_str()},
	  _text{other._text},
	  _font{Font::OpenFont(other._path.c_str(), 0)},
	  _color{other._color},
	  _path{other._path}
{
}

Text& Text::operator=(const Text& other)
{
	if (this != &other)
	{
		delete _font;

		_text = other._text;
		_font = Font::OpenFont(other._path.c_str(), 0);
		_path = other._path;
		_color = other._color;
	}
	return *this;
}

Text::Text(Text&& other) noexcept
	: Renderable{other._path.c_str()},
	  _text{other._text},
	  _font{other._font},
	  _color{other._color},
	  _path{other._path}
{
	other._font = nullptr;
}

Text& Text::operator=(Text&& other) noexcept
{
	if (this != &other)
	{
		delete _font;

		_text = other._text;
		_font = other._font;
		_path = other._path;
		_color = other._color;

		other._font = nullptr;
	}
	return *this;
}

Text::~Text() {}

void Text::Render(Rendering::Renderer* renderer, const Transform& transform)
{

	if (_font == nullptr)
	{
		std::cerr << "Font not loaded" << '\n';
		return;
	}

	Rendering::Surface* surface = Font::RenderText_Solid(_font, _text.c_str(), _color);

	if (surface == nullptr)
	{
		std::cerr << "Error creating surface: " << Rendering::GetError() << '\n';
		return;
	}

	Rendering::Texture* texture = Rendering::CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr)
	{
		std::cerr << "Error creating texture: " << Rendering::GetError() << '\n';
		Rendering::FreeSurface(surface);
		Rendering::DestroyTexture(texture);
		return;
	}

	Rendering::Rect dstRect = { transform.position.GetX(), transform.position.GetY(), surface->w, surface->h};

	Rendering::RenderCopy(renderer, texture, nullptr, &dstRect);

	Rendering::FreeSurface(surface);
	Rendering::DestroyTexture(texture);
}

void Text::SetText(const std::string& text)
{
	_text = text;
}

void Text::SetFontSize(const size_t size)
{
	Font::SetFontSize(_font, size);
}

void Text::unloadText()
{
	if (_font != nullptr)
	{
		Font::CloseFont(_font);
		_font == nullptr;
	}
}
