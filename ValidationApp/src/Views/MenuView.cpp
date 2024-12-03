#include "MenuView.hpp"


MenuView::MenuView(Scene& scene, const std::string& title, unsigned char numOfButtons, const std::string& pathToFont,
	const Math::Vector2& startPos, const Math::Vector2& scale, int margin, int fontSize) :
	IView{ scene, pathToFont }, _buttons{}
{
	InitTitle(title, fontSize);
	InitButtons(numOfButtons, startPos, scale, margin, fontSize);
}

void MenuView::InitTitle(const std::string& title, int fontSize)
{
	_title = std::shared_ptr<GameObject>{ _scene.Instantiate({ {100.0f, 100.0f}, 0.0f, {200.0f, 100.0f} }) };
	_title->AddComponent<Ui::Text>(title, _fontPath, DEFAULT_COLOR)->SetFontSize(fontSize);
}

void MenuView::InitButtons(unsigned char numOfButtons, const Math::Vector2& startPos, const Math::Vector2& scale, 
	int margin, int fontSize)
{
	auto pos = startPos;
	for (unsigned char i = 0; i < numOfButtons; ++i)
	{
		_buttons.emplace(i, std::shared_ptr<GameObject> { _scene.Instantiate({ pos, 0.0f, scale }) });

		// Image
		_buttons[i]->AddComponent<Ui::Image>("menu_button")->SetColor(DEFAULT_COLOR);

		// SFX
		auto& sfx = *_buttons[i]->AddComponent<Audio::SFXSource>();
		sfx.SetClip(DEFAULT_BUTTON_SFX);
		sfx.SetVolume(20);

		// Button
		auto& button = *_buttons[i]->AddComponent<Ui::Button>();
		button.SetOnLeftMouseClick([&sfx]() -> void
			{
				sfx.Play();
			}, "Default");

		// Text
		_buttons[i]->AddComponent<Ui::Text>(
			std::string{"Button" + std::to_string(i)}, _fontPath, DEFAULT_COLOR)->SetFontSize(fontSize);
		_buttons[i]->GetComponent<Ui::Text>().SetPosition(pos);

		pos.SetY(pos.GetY() + scale.GetY() + margin);
	}
}

void MenuView::SetButtonTextPosition(int id, const Math::Vector2& position)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Text>().SetPosition(position);
		}	
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Text>().SetPosition(position);
	}
}

void MenuView::SetButtonText(int id, const std::string& text)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Text>().SetText(text);
		}
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Text>().SetText(text);
	}
}

void MenuView::SetButtonOnLeftMouseClick(int id, std::function<void()> func, const std::string& category)
{
	_buttons[id]->GetComponent<Ui::Button>().SetOnLeftMouseClick(func, category);
}

std::shared_ptr<GameObject>& MenuView::GetButton(unsigned char id)
{
	return _buttons[id];
}

Ui::Text& MenuView::GetButtonText(unsigned char id)
{
	return GetButton(id)->GetComponent<Ui::Text>();
}
