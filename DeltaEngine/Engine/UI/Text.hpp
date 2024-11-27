#pragma once
#include "Font.hpp"
#include <iostream>
#include <string>
namespace Ui
{
	class Text
	{
	   public:
			Text(const std::string& text, const std::string& path, const int size, const int x, const int y, const Rendering::Color& color);
			~Text();
			void Render();
			void unloadText();
	   private:
			std::string _text;
			Font::Font* _font;
			int _size;
			int _x, _y;
			Rendering::Color _color;
	};
}

