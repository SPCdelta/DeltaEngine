#pragma once
#include "UIObject.hpp"
#include "Font.hpp"
#include <iostream>
#include <string>
namespace ui
{
	class Text
	{
	   public:
			Text(std::string text, std::string path, int size, int x, int y, Rendering::Color color, Rendering::Renderer* renderer);
			~Text();
			void renderText();
			void unloadText();
	   private:
			std::string _text;
			Font::Font* _font;
			int _size;
			int _x, _y;
			Rendering::Color _color;
			Rendering::Renderer* _renderer;
	};
}

