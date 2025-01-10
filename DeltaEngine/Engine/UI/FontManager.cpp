#include "FontManager.hpp"

FontManager FontManager::instance;

FontManager::FontManager() 
{

}

FontManager::~FontManager()
{ 
    _fonts.clear();
    TTF_Quit();
}