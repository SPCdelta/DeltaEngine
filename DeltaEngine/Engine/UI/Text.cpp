#include "Text.hpp"

ui::Text::Text(std::string text, std::string path, int size, int x, int y, Rendering::Color color)
	: text{text}, size{size}, x{x}, y{y}, color{color}
{
	font = Font::OpenFont(path.c_str(), size);

	if (font == nullptr)
	{
		std::cerr << "Error loading font: " << Font::GetError() << std::endl;
	}
}
