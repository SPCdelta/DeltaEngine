#include "WeaponSelectionView.hpp"

WeaponSelectionView::WeaponSelectionView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, 
	const Math::Vector2& scale) 
	: IView(scene, fontName, startPos, scale)
{
	_window = _scene.Instantiate({ _pos, 0.0f, _scale });
	_window->AddComponent<Ui::Image>(WINDOW_FRAME_SPRITENAME);
	SetCenter(); // set center must be called after initializing window
	InitTitle();
	InitBody();
}

const Math::Vector2& WeaponSelectionView::GetSize() const
{
	return _scale;
}

void WeaponSelectionView::SetCenter()
{
	auto& vp = _scene.GetWindow()->GetViewport();
	auto xPos = vp.width / 2 - GetSize().GetX() / 2;
	auto yPos = vp.height / 2 - GetSize().GetY() / 2;
	_pos = { xPos, yPos };
	_window->transform->position = _pos;
}

void WeaponSelectionView::InitTitle()
{
	auto& text = *_window->AddComponent<Ui::Text>(TITLE, _fontName, static_cast<int>(_scale.Magnitude() *
		TITLE_SCALE), TEXT_COLOR);
	auto xPos = (_pos.GetX() + _scale.GetX() / 2) - (Font::GetFontSize(text.GetFont(), text.GetText()).GetX() / 2);
	auto yPos = _pos.GetY();
	yPos += _scale.GetY() * TITLE_MARGINY_SCALE;
	text.SetPosition({ xPos, yPos });
}

void WeaponSelectionView::InitBody()
{

}
