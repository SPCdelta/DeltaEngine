#include "MenuView.hpp"


MenuView::MenuView(Scene& scene, const std::string& title, Uint8 numOfButtons, const std::string& pathToFont, const Math::Vector2& startPos, const Math::Vector2& scale, 
	int margin, int fontSize) 
	: IView{ scene, pathToFont, startPos, scale }, 
	  _buttons{}
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
			item->transform->position = position;
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
			item->transform->scale = scale;
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

void MenuView::InitButtons(unsigned char numOfButtons, const Math::Vector2& startPos, const Math::Vector2& scale, int margin, int fontSize)
{
	auto pos = startPos;
	pos.SetY(pos.GetY() + scale.GetY() + margin);
	for (unsigned char i = 0; i < numOfButtons; ++i)
	{
		_buttons.push_back(std::shared_ptr<GameObject> { _scene.Instantiate({ pos, 0.0f, scale }) });

		// Image
		_buttons[i]->AddComponent<Ui::Image>(DEFAULT_BUTTON_TEXTURE.c_str());

		// SFX
		auto& sfx = *_buttons[i]->AddComponent<Audio::SFXSource>("", false, false);

		// Button
		auto& button = *_buttons[i]->AddComponent<Ui::Button>();

		// Text
		Ui::Text* text = _buttons[i]->AddComponent<Ui::Text>(std::string{"Button" + std::to_string(i)}, _fontName, fontSize, DEFAULT_COLOR);
		text->SetPosition(pos);

		button.SetOnMousePressed([text]()
		{
			text->SetColor({60,60,60});
		}, "UI-Button-ViewMenu");

		pos.SetY(pos.GetY() + scale.GetY() + margin);
	}
}

void MenuView::SetButtonTextPosition(int id, const Math::Vector2& position)
{
	if (id == -1)
	{
		for (auto item : _buttons)
			item->GetComponent<Ui::Text>().SetPosition(position);	
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
			item->GetComponent<Ui::Text>().AddPosition(position);
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
			item->GetComponent<Ui::Text>().SetText(text);
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
			item->GetComponent<Ui::Text>().SetFontSize(textSize);
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
			item->GetComponent<Ui::Button>().SetOnLeftMouseClick(func, category);
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
			item->GetComponent<Audio::SFXSource>().SetClip(sfxPath);
	}
	else
	{
		_buttons[id]->GetComponent<Audio::SFXSource>().SetClip(sfxPath);
	}
}

void MenuView::SetButtonOnLeftMouseClickLoadScene(int id, Scene* scene, const std::string& sceneName, const std::string& category, const std::string& sceneData)
{
	auto& btn = _buttons[id]->GetComponent<Ui::Button>();
	btn.SetOnLeftMouseClick([this, scene, sceneName, &btn, sceneData]() -> void
	{
		if (!sceneData.empty())
			scene->StoreUserData({{"fileName" , sceneData }});

		scene->LoadScene(sceneName);
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
			item->GetComponent<Ui::Text>().SetColor(color);
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
			item->GetComponent<Ui::Image>().SetSprite(textureName);
	}
	else
	{
		_buttons[id]->GetComponent<Ui::Image>().SetSprite(textureName);
	}
}


std::shared_ptr<GameObject>& MenuView::GetButton(Uint8 id)
{
	return _buttons[id];
}

Ui::Text& MenuView::GetButtonText(Uint8 id)
{
	return GetButton(id)->GetComponent<Ui::Text>();
}

const Math::Vector2& MenuView::GetSize() const
{
	return _scale;
}
