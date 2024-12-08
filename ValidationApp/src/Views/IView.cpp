#include "IView.hpp"

IView::IView(Scene& scene, const std::string& fontName) : _fontName{ fontName }, _scene(scene)
{

}

void IView::SetFont(const std::string& fontName)
{
	_fontName = fontName;
}