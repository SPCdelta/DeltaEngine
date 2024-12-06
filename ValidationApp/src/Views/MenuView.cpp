#include "MenuView.hpp"


MenuView::MenuView(Scene& scene, const std::string& title, Rendering::UnsignInt8 numOfButtons, const std::string& pathToFont,
	const Math::Vector2& startPos, const Math::Vector2& scale, int margin, int fontSize) :
	IView{ scene, pathToFont }, _buttons{}
{
	InputManager::activateCategory(title);
	InitTitle(title, fontSize, startPos);
	InitButtons(numOfButtons, startPos, scale, margin, fontSize);
}

void MenuView::SetButtonPosition(int id, const Math::Vector2& position)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->transform->position = position;
		}
	}
	else
	{
		_buttons[id]->transform->position = position;
	}
}

void MenuView::SetButtonScale(int id, const Math::Vector2& scale)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->transform->scale = scale;
		}
	}
	else
	{
		_buttons[id]->transform->scale = scale;
	}
}

void MenuView::InitTitle(const std::string& title, int fontSize, const Math::Vector2& startPos)
{
	_title = std::shared_ptr<GameObject>{ _scene.Instantiate({ {100.0f, 100.0f}, 0.0f, {200.0f, 100.0f} }) };
	auto& text = *_title->AddComponent<Ui::Text>(title, _fontName, fontSize, DEFAULT_COLOR);
	text.SetPosition(startPos);
}

void MenuView::InitButtons(unsigned char numOfButtons, const Math::Vector2& startPos, const Math::Vector2& scale, 
	int margin, int fontSize)
{
	auto pos = startPos;
	pos.SetY(pos.GetY() + scale.GetY() + margin);
	for (unsigned char i = 0; i < numOfButtons; ++i)
	{
		_buttons.emplace(i, std::shared_ptr<GameObject> { _scene.Instantiate({ pos, 0.0f, scale }) });

		// Image
		_buttons[i]->AddComponent<Ui::Image>(DEFAULT_BUTTON_TEXTURE.c_str());

		// SFX
		auto& sfx = *_buttons[i]->AddComponent<Audio::SFXSource>("", false, false);

		// Button
		auto& button = *_buttons[i]->AddComponent<Ui::Button>();

		// Text
		_buttons[i]->AddComponent<Ui::Text>(
			std::string{"Button" + std::to_string(i)}, _fontName, fontSize, DEFAULT_COLOR);
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

void MenuView::AddButtonTextPosition(int id, const Math::Vector2& position)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Text>().AddPosition(position);
		}
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Text>().AddPosition(position);
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

void MenuView::SetButtonTextSize(int id, int textSize)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Text>().SetFontSize(textSize);
		}
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Text>().SetFontSize(textSize);
	}
}

void MenuView::SetButtonOnLeftMouseClick(int id, std::function<void()> func, const std::string& category)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Button>().SetOnLeftMouseClick(func, category);
		}
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Button>().SetOnLeftMouseClick(func, category);
	}
}

void MenuView::SetButtonSFX(int id, const std::string& sfxPath)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Audio::SFXSource>().SetClip(sfxPath);
		}
	}
	else
	{
		_buttons[id]->GetComponent<Audio::SFXSource>().SetClip(sfxPath);
	}
}

void MenuView::SetButtonOnLeftMouseClickLoadScene(int id, Scene& scene, const std::string& sceneName, 
	const std::string& category)
{
	auto& btn = _buttons[id]->GetComponent<Ui::Button>();
	btn.SetOnLeftMouseClick([&scene, sceneName, &btn]() -> void
		{
			scene.LoadScene(sceneName);
		}, category);
}

void MenuView::SetTitleTextPosition(const Math::Vector2& position)
{
	_title->GetComponent<Ui::Text>().SetPosition(position);
}

void MenuView::SetTitleTextSize(int size)
{
	_title->GetComponent<Ui::Text>().SetFontSize(size);
}

void MenuView::SetButtonTextColor(int id, const Rendering::Color& color)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Text>().SetColor(color);
		}
	}
	else
	{
		_buttons[id]-> GetComponent<Ui::Text>().SetColor(color);
	}
}

void MenuView::SetTitleTextColor(const Rendering::Color& color)
{
	_title->GetComponent<Ui::Text>().SetColor(color);
}

void MenuView::SetButtonTexture(int id, const std::string& textureName)
{
	if (id == -1)
	{
		for (auto item : _buttons)
		{
			item.second->GetComponent<Ui::Image>().SetSprite(textureName);
		}
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Image>().SetSprite(textureName);
	}
}


std::shared_ptr<GameObject>& MenuView::GetButton(Rendering::UnsignInt8 id)
{
	return _buttons[id];
}

Ui::Text& MenuView::GetButtonText(Rendering::UnsignInt8 id)
{
	return GetButton(id)->GetComponent<Ui::Text>();
}