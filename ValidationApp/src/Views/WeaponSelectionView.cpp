#include "WeaponSelectionView.hpp"
#include "../Scripts/PlayerBehaviour.hpp"

WeaponSelectionView::WeaponSelectionView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, 
	const Math::Vector2& scale, const std::string& sceneName) 
	: IView(scene, fontName, startPos, scale), _sceneName{sceneName}
{
	_window = _scene.Instantiate({ _pos, 0.0f, _scale });
	_window->AddComponent<Ui::Image>(WINDOW_FRAME_SPRITENAME)->SetLayer(Layer::Default);
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
	// don't change order!
	InitGun();
	InitBoomerang();
	InitBow();
	ToggleVisibilityWeapons(false);
	InitButtons();
}

void WeaponSelectionView::InitGun()
{
	auto xPos = _window->transform->position.GetX() + _scale.Magnitude() * MARGINX_SCALE;
	auto yPos = _scale.GetY() / 2;

	_gunFrame = _scene.Instantiate({ {xPos, yPos}, 0.0f, _scale * WEAPON_SCALE });
	_gunFrame->AddComponent<Ui::Image>("hotbar_slot")->SetLayer(Layer::Foreground);
	_gunFrame->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this]() -> void
		{
			_weapon = "gun";
			ToggleVisibilityWeapons(false);
			_gunFrame->GetComponent<Ui::Image>().SetVisible(true);
		}, "WeaponSelection");
	_gun = _scene.Instantiate({ {xPos, yPos}, 0.0f, _scale * WEAPON_SCALE });
	_gun->AddComponent<Ui::Image>(GUN_SPRITE)->SetLayer(Layer::Foreground);

	auto& text = *_gun->AddComponent<Ui::Text>("Gun", _fontName, _scale.Magnitude() * BODY_TEXT_SCALE, TEXT_COLOR);
	SetTextCenterBottom(*_gun.get(), text);

	_gun->AddComponent<Ui::Button>();
}

void WeaponSelectionView::InitBoomerang()
{
	auto xPos = _gun->transform->position.GetX() + _gun->transform->scale.GetX() / 2 + _scale.Magnitude() * MARGINX_SCALE;
	auto yPos = _scale.GetY() / 2;

	_boomerangFrame = _scene.Instantiate({ {xPos, yPos}, 0.0f, _scale * WEAPON_SCALE });
	_boomerangFrame->AddComponent<Ui::Image>("hotbar_slot")->SetLayer(Layer::Foreground);
	_boomerangFrame->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this]() -> void
		{
			_weapon = "boomerang";
			ToggleVisibilityWeapons(false);
			_boomerangFrame->GetComponent<Ui::Image>().SetVisible(true);
		}, "WeaponSelection");
	_boomerang = _scene.Instantiate({ {xPos, yPos}, 0.0f, _scale * WEAPON_SCALE });
	_boomerang->AddComponent<Ui::Image>(BOOMERANG_SPRITE)->SetLayer(Layer::Foreground);

	auto& text = *_boomerang->AddComponent<Ui::Text>("Boomerang", _fontName, _scale.Magnitude() * BODY_TEXT_SCALE, TEXT_COLOR);
	SetTextCenterBottom(*_boomerang.get(), text);

	_boomerang->AddComponent<Ui::Button>();
}

void WeaponSelectionView::InitBow()
{
	auto xPos = _boomerang->transform->position.GetX() + _boomerang->transform->scale.GetX() / 2 + _scale.Magnitude() * MARGINX_SCALE;
	auto yPos = _scale.GetY() / 2;

	_bowFrame = _scene.Instantiate({ {xPos, yPos}, 0.0f, _scale * WEAPON_SCALE });
	_bowFrame->AddComponent<Ui::Button>()->SetOnLeftMouseClick([this]() -> void
		{
			_weapon = "bow";
			ToggleVisibilityWeapons(false);
			_bowFrame->GetComponent<Ui::Image>().SetVisible(true);
		}, "WeaponSelection"); _bowFrame->AddComponent<Ui::Image>("hotbar_slot")->SetLayer(Layer::Foreground);
	_bow = _scene.Instantiate({ {xPos, yPos}, 0.0f, _scale * WEAPON_SCALE });
	_bow->AddComponent<Ui::Image>(BOW_SPRITE)->SetLayer(Layer::Foreground);

	auto& text = *_bow->AddComponent<Ui::Text>("Bow", _fontName, _scale.Magnitude() * BODY_TEXT_SCALE, TEXT_COLOR);
	SetTextCenterBottom(*_bow.get(), text);

	_bow->AddComponent<Ui::Button>();
}

void WeaponSelectionView::SetTextCenterBottom(const GameObject& gameObject, Ui::Text& text)
{
	auto xPos = gameObject.transform->position.GetX();
	auto yPos = gameObject.transform->position.GetY();

	auto xScale = gameObject.transform->scale.GetX();
	auto yScale = gameObject.transform->scale.GetY();

	auto textXPos = (xPos + xScale / 2) - (Font::GetFontSize(text.GetFont(), text.GetText()).GetX() / 2);
	auto textYPos = yPos;
	textYPos += yScale;
	text.SetPosition({ textXPos, textYPos });
}

void WeaponSelectionView::ToggleVisibilityWeapons(bool visible)
{
	_boomerangFrame->GetComponent<Ui::Image>().SetVisible(visible);
	_bowFrame->GetComponent<Ui::Image>().SetVisible(visible);
	_gunFrame->GetComponent<Ui::Image>().SetVisible(visible);
}

void WeaponSelectionView::InitButtons()
{
	InitHomeBtn();
	InitConfirmButton();
}

void WeaponSelectionView::InitConfirmButton()
{
	auto xPos = _pos.GetX() + (_scale.GetX() * CONFIRM_BTN_MARGINX_SCALE);
	auto yPos = _pos.GetY() + _scale.GetY() - _scale.Magnitude() * BTN_MARGINY_SCALE;
	auto& quit = *_scene.Instantiate({ {xPos, yPos}, 0.0f, {0, 0} });
	auto& quitText = *quit.AddComponent<Ui::Text>("Confirm", _fontName, static_cast<int>(_scale.Magnitude() * BUTTON_TEXT_SCALE),
		BODY_TEXT_COLOR);
	quit.transform->scale = Font::GetFontSize(quitText.GetFont(), quitText.GetText());
	auto& quitBtn = *quit.AddComponent<Ui::Button>();
	quitBtn.SetOnLeftMouseClick([this]() -> void
		{
			if (_weapon.empty()) return;

			std::shared_ptr<GameObject> playerObject{ _scene.Instantiate() };
			// TODO: remove unnecessary components for initialising playerBehaviourScript?
			std::shared_ptr<AnimationSheet> playerSheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 0, 0, 0, 0, 0, 0, 0);
			playerSheet->AddCustomAnimation("death", 0, 0, 0);
			playerObject->AddComponent<Sprite>("layerPlayer", playerSheet)->SetLayer(Layer::Player);
			playerObject->AddComponent<Audio::SFXSource>("", false, false);
			playerObject->AddComponent<BoxCollider>();
			playerObject->AddComponent<Rigidbody>();
			auto& playerBehaviour = *playerObject->AddComponent<PlayerBehaviour>();			
			playerBehaviour.LoadPlayer();
			playerBehaviour.SetWeapon(_weapon);
			playerBehaviour.SavePlayer();
			playerObject->SetTag("player");

			_scene.LoadScene(_sceneName);
		}, "ScoreScreen");
}

void WeaponSelectionView::InitHomeBtn()
{
	auto xPos = _pos.GetX() + (_scale.GetX() * HOME_BTN_MARGINX_SCALE);
	auto yPos = _pos.GetY() + _scale.GetY() - _scale.Magnitude() * BTN_MARGINY_SCALE;
	auto& home = *_scene.Instantiate({ {xPos, yPos}, 0.0f, {0, 0} });
	auto& homeText = *home.AddComponent<Ui::Text>("Return to menu", _fontName, static_cast<int>(_scale.Magnitude() * BUTTON_TEXT_SCALE),
		BODY_TEXT_COLOR);
	home.transform->scale = Font::GetFontSize(homeText.GetFont(), homeText.GetText());
	auto& homeBtn = *home.AddComponent<Ui::Button>();
	homeBtn.SetOnLeftMouseClick([this]() -> void
		{
			_scene.LoadScene("MainMenuScene");
		}, "ScoreScreen");
}