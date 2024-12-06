#include "IView.hpp"

IView::IView(Scene& scene, const std::string& pathToFont) : _fontName{pathToFont}, _scene(scene)
{

}

void IView::SetFont(const std::string& pathToFont)
{
	_fontName = pathToFont;
}