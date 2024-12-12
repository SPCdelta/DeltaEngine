#include "IView.hpp"

IView::IView(Scene& scene, const std::string& fontName, const Math::Vector2& pos, const Math::Vector2& scale) 
	: _fontName{ fontName }, _scene(scene), _scale{scale}, _pos{pos}
{

}

void IView::SetFont(const std::string& fontName)
{
	_fontName = fontName;
}

const Math::Vector2& IView::GetPos() const
{
	return _pos;
}
