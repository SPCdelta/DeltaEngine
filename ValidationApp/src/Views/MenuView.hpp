#pragma once

#include "Engine/Delta.hpp"

#include "IView.hpp"

#include <memory>
#include <functional>
#include <vector>

class MenuView : public IView
{
public: // Uint8 is used to limit buttons to 255. Change to different type if needed. Scale is applied to every button element
	MenuView(Scene& scene, const std::string& title, Uint8 numOfButtons, const std::string& fontPath, const Math::Vector2& startPos, const Math::Vector2& scale, 
		int margin, int fontSize);
	
	void SetButtonPosition(int id, const Math::Vector2& position);
	void SetButtonScale(int id, const Math::Vector2& scale);

	void SetButtonTextPosition(int id, const Math::Vector2& position);
	void AddButtonTextPosition(int id, const Math::Vector2& position);

	void SetButtonText(int id, const std::string& text);
	void SetButtonTextSize(int id, int textSize);

	void SetButtonOnLeftMouseClick(int id, std::function<void()> func, const std::string& category);
	void SetButtonSFX(int id, const std::string& sfxPath);
	void SetButtonOnLeftMouseClickLoadScene(int id, Scene* scene, const std::string& sceneName, const std::string& category, const std::string& sceneData = "");

	void SetTitleTextPosition(const Math::Vector2& position);
	void SetTitleTextSize(int size);

	void SetButtonTextColor(int id, const Rendering::Color& color);
	void SetTitleTextColor(const Rendering::Color& color);

	void SetButtonTexture(int id, const std::string& textureName);

	std::shared_ptr<GameObject>& GetButton(Uint8 id); // Unsigned char is used as id

	Ui::Text& GetButtonText(Uint8 id);

	const Math::Vector2& GetSize() const override;

private:
	void InitTitle(const std::string& title, int fontSize, const Math::Vector2& startPos);
	void InitButtons(unsigned char numOfButtons, const Math::Vector2& startPos, const Math::Vector2& scale, int margin, int fontSize);

	std::shared_ptr<GameObject> _title;	
	std::vector<std::shared_ptr<GameObject>> _buttons;

	const std::string DEFAULT_BUTTON_TEXTURE = "scroll3";
};