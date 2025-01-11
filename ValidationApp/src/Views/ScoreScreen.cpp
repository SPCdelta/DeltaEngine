#include "ScoreScreen.hpp"

ScoreScreen::ScoreScreen(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale, const std::string& title, 
	const Rendering::Color& textColor, int coins) 
	: IView(scene, fontName, startPos, scale)
{
	_window = _scene.Instantiate({ _pos, 0.0f, _scale });
	_window->AddComponent<Ui::Image>(WINDOW_FRAME_SPRITENAME);
	SetCenter(); // Set center must be called after initializing window
	InitTitle(title, textColor);
	InitBody(coins);
}

const Math::Vector2& ScoreScreen::GetSize() const
{
	return _scale;
}

void ScoreScreen::SetCenter()
{
	auto& vp = _scene.GetWindow()->GetViewport();
	auto xPos = vp.width / 2 - GetSize().GetX() / 2;
	auto yPos = vp.height / 2 - GetSize().GetY() / 2;
	_pos = { xPos, yPos };
	_window->transform->position = _pos;
}

void ScoreScreen::InitTitle(const std::string& title, const Rendering::Color& textColor)
{
	auto& text = *_window->AddComponent<Ui::Text>(title, _fontName, static_cast<int>(_scale.Magnitude() * TITLE_SCALE), textColor);
	auto xPos = _scale.GetX() / 2 - Font::GetFontSize(text.GetFont(), text.GetText()).GetX() / 2;
	auto yPos = 0.f;
	yPos += _scale.GetY() * TITLE_MARGINY_SCALE;
	text.SetPosition({ xPos, yPos });
}

void ScoreScreen::InitBody(int coins)
{
	auto& score = *_scene.Instantiate({ _pos, 0.0f, _scale });
	auto& text = *score.AddComponent<Ui::Text>(std::string{ "Your score was: " + std::to_string(coins) }, 
		_fontName, static_cast<int>(_scale.Magnitude() * BODY_TEXT_SCALE), BODY_TEXT_COLOR);

	auto xPos = _scale.GetX() / 2 - Font::GetFontSize(text.GetFont(), text.GetText()).GetX() / 2;
	auto yPos = _scale.GetY() / 2;
	text.SetPosition({xPos, yPos});

	InitButtons();
}

void ScoreScreen::InitButtons()
{
	InitHomeBtn();
	InitQuitBtn();
}

void ScoreScreen::InitQuitBtn()
{
	auto xPos = _pos.GetX() + (_scale.GetX() * QUIT_BTN_MARGINX_SCALE);
	auto yPos = _pos.GetY() + _scale.GetY() - _scale.Magnitude() * BTN_MARGINY_SCALE;

	auto& quit = *_scene.Instantiate({ {xPos, yPos}, 0.0f, {0, 0} });
	auto& quitText = *quit.AddComponent<Ui::Text>("Quit", _fontName, static_cast<int>(_scale.Magnitude() * BUTTON_TEXT_SCALE), BODY_TEXT_COLOR);
	quit.transform->scale = Font::GetFontSize(quitText.GetFont(), quitText.GetText());

	auto& quitBtn = *quit.AddComponent<Ui::Button>();
	quitBtn.SetOnLeftMouseClick([]() -> void
	{
		Application::Quit();
	}, "ScoreScreen");
}

void ScoreScreen::InitHomeBtn()
{
	auto xPos = _pos.GetX() + (_scale.GetX() * HOME_BTN_MARGINX_SCALE);
	auto yPos = _pos.GetY() + _scale.GetY() - _scale.Magnitude() * BTN_MARGINY_SCALE;

	auto& home = *_scene.Instantiate({ {xPos, yPos}, 0.0f, {0, 0} });
	auto& homeText = *home.AddComponent<Ui::Text>("Return to menu", _fontName, static_cast<int>(_scale.Magnitude() * BUTTON_TEXT_SCALE), BODY_TEXT_COLOR);
	home.transform->scale = Font::GetFontSize(homeText.GetFont(), homeText.GetText());

	auto& homeBtn = *home.AddComponent<Ui::Button>();
	homeBtn.SetOnLeftMouseClick([this]() -> void
	{
		_scene.LoadScene("MainMenuScene");
	}, "ScoreScreen");
}
