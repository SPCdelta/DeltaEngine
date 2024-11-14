#pragma once
#include "UIObject.hpp"
#include <iostream>
#include <string>
namespace ui
{
	class Text : UIObject
	{
	   public:
			Text(std::string font, int size);
			std::string getFont();
	   private:
		std::string font;
		int size;
		// allignment
		// color
	};
}

