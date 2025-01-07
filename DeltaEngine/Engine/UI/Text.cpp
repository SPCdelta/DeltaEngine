#include "Text.hpp"

using namespace Ui;
using namespace Rendering;

Text::Text(const std::string& text, const std::string& fontName, int fontSize,
		   const Rendering::Color& color)
	: 
	  _fontName{ fontName },
	  _fontSize{ fontSize },
	  _text{text},
	  _color{color},
	  _font{ ResourceManager::GetFont(fontName, fontSize)},
	  _backgroundColor{0,0,0,0}
{
	if (_font == nullptr)
	{
		std::cerr << "Error loading font: " << Font::GetError() << std::endl;
	}
}

//Text::Text(const Text& other)
//	: 
//	  _text{other._text},
//	  _font{other._font},
//	  _color{other._color},
//	_fontName{ other._fontName },
//	_fontSize{ other._fontSize },
//	_background{ other._background },
//	_backgroundColor{ other._backgroundColor },
//	_position{ other._position }
//{
//	int bp = 0;
//}

//Text& Text::operator=(const Text& other)
//{
//	if (this != &other)
//	{
//		_text = other._text;
//		_font = other._font;
//		_color = other._color;
//		_fontName = other._fontName;
//		_fontSize = other._fontSize;
//		_background =other._background;
//		_backgroundColor = other._backgroundColor;
//		_position =  other._position;
//	}
//	return *this;
//}

//Text::Text(Text&& other) noexcept
//	: _text{other._text},
//	  _font{other._font},
//	  _color{other._color},
//	  _fontName{other._fontName},
//	_fontSize{other._fontSize},
//	_background{other._background },
//	_backgroundColor{other._backgroundColor},
//	_position{other._position}
//
//{
//	int bp = 0;
//}

//Text& Text::operator=(Text&& other) noexcept
//{
//	if (this != &other)
//	{
//		_text = other._text;
//		_font = other._font;
//		_color = other._color;
//		_fontName = other._fontName;
//		_fontSize = other._fontSize;
//		_background = other._background;
//		_backgroundColor = other._backgroundColor;
//		_position = other._position;
//
//	}
//	return *this;
//}

void Text::Render(Renderer* renderer, const Transform& transform)
{

	if (_font == nullptr)
	{
		std::cerr << "Font not loaded" << '\n';
		return;
	}

	Surface* surface = Font::RenderText_Solid(_font->GetFont(), _text.c_str(), _color);

	if (surface == nullptr)
	{
		std::cerr << "Error creating surface: " << GetError() << '\n';
		return;
	}

	Texture* texture = CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr)
	{
		std::cerr << "Error creating texture: " << GetError() << '\n';
		FreeSurface(surface);
		DestroyTexture(texture);
		return;
	}

	Rect dstRect;
	if (_position.IsNonZero()) 
	{
		dstRect = { static_cast<int>(_position.GetX()), static_cast<int>(_position.GetY()), surface->w, surface->h };
	} else 
	{
		dstRect = { static_cast<int>(transform.position.GetX()), static_cast<int>(transform.position.GetY()), surface->w, surface->h};
	}

	if (_background)
		RenderRect(renderer, dstRect, _backgroundColor);

	RenderCopy(renderer, texture, nullptr, &dstRect);

	FreeSurface(surface);
	DestroyTexture(texture);
}

void Text::AddPosition(const Math::Vector2& position)
{
	_position += position;
}

void Text::SetText(const std::string& text)
{
	_text = text;
}

void Text::SetFont(const std::string& fontName)
{
	_fontName = fontName;
	_font = ResourceManager::GetFont(_fontName, _fontSize);
}

const std::string& Ui::Text::GetText() const
{
	return _text;
}

void Text::SetFontSize(int size)
{
	_fontSize = size;
	_font = ResourceManager::GetFont(_fontName, _fontSize);
}

int Ui::Text::GetFontSize() const
{
	return _fontSize;
}

std::shared_ptr<FontWrapper> Ui::Text::GetFont() const
{
	return _font;
}

void Text::SetPosition(const Math::Vector2& position)
{
	_position = position;
}

void Text::SetBackground(Rendering::Color color) {
	_background = true;
	_backgroundColor = color;
}
void Text::SetColor(const Rendering::Color& color)
{
	_color = color;
}

const Math::Vector2& Ui::Text::GetPosition() const
{
	return _position;
}

Transform Ui::Text::GetTransform()
{
	return Transform(_position, 0.0f, {}, nullptr);
}
