#include "WindowView.hpp"

WindowView::WindowView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, IView& body, const Math::Vector2& margin)
	: IView(scene, fontName, startPos, {}), _margin{margin}
{
	_window = _scene.Instantiate({ _pos, 0.0f, _scale });
	_window->AddComponent<Ui::Image>(WINDOW_FRAME_SPRITENAME);
	SetCenter(); // set center must be called after initializing window
}

const Math::Vector2& WindowView::GetSize() const
{
	return _scale;
}

void WindowView::SetCenter()
{
	auto vp = _scene.GetWindow()->GetViewport();
	auto xPos = vp.width / 2 - GetSize().GetX() / 2;
	auto yPos = vp.height / 2 - GetSize().GetY() / 2;
	_pos = { xPos, yPos };
	_window->transform->position = _pos;
}

void WindowView::SetBody(IView& body)
{
	auto xPos = _pos.GetX() + _margin.GetX();
	auto yPos = _pos.GetY() + _margin.GetY();
	body.SetPosition({xPos, yPos});
}
