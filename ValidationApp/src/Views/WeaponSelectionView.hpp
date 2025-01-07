#pragma once

#include "Engine/Delta.hpp"
#include "IView.hpp"

class WeaponSelectionView : public IView
{
public:
	WeaponSelectionView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale);
	const Math::Vector2& GetSize() const override;
	void SetCenter() override;
private:
	void InitTitle();
	void InitBody();
	void InitGun();
	void InitBoomerang();
	void InitBow();
	void SetTextCenterBottom(const GameObject& gameObject, Ui::Text& text);
	void ToggleVisibilityWeapons(bool visible);
	void InitButtons();
	void InitConfirmButton();
	void InitHomeBtn();
	const Rendering::Color TEXT_COLOR = { 255, 255 ,255, 255 };
	const float TITLE_SCALE = 0.02f;
	const float TITLE_MARGINY_SCALE = 0.15f;
	const float BUTTON_TEXT_SCALE = 0.015f;
	const float HOME_BTN_MARGINX_SCALE = 0.15f;
	const float CONFIRM_BTN_MARGINX_SCALE = 0.7f;
	const float BTN_MARGINY_SCALE = 0.15f;
	const Rendering::Color BODY_TEXT_COLOR = { 255, 255 ,255, 255 };
	const std::string WINDOW_FRAME_SPRITENAME = "window_frame";
	const float WEAPON_SCALE = 0.2f;
	const float MARGINX_SCALE = 0.1f;
	std::shared_ptr<GameObject> _window;
	std::shared_ptr<GameObject> _gun;
	std::shared_ptr<GameObject> _gunFrame;
	std::shared_ptr<GameObject> _bow;
	std::shared_ptr<GameObject> _bowFrame;
	std::shared_ptr<GameObject> _boomerang;
	std::shared_ptr<GameObject> _boomerangFrame;
	const std::string FRAME_SPRITE = "weapon_frame";
	const std::string TITLE = "SELECT YOUR WEAPON";
	const std::string GUN_SPRITE = "gun";
	const std::string BOW_SPRITE = "bow";
	const std::string BOOMERANG_SPRITE = "boomerang";
	std::string _weapon;
};

