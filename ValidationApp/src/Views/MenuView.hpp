#pragma once

#include "IView.hpp"
#include <memory>
#include <functional>
#include "Engine/Delta.hpp"

class MenuView : public IView
{
public:
	/* 
	* we use unsigned char to limit buttons to 255. change to different type if needed
	* scale is applied to every button element
	*/
	MenuView(Scene& scene, const std::string& title, unsigned char numOfButtons, const std::string& fontPath, const Math::Vector2& startPos, const Math::Vector2& scale, int margin, int fontSize);
	void SetButtonTextPosition(int id, const Math::Vector2& position);
	void SetButtonText(int id, const std::string& text);
	void SetButtonOnLeftMouseClick(int id, std::function<void()> func, const std::string& category);
	void SetButtonSFX(int id, const std::string& sfxPath);
	std::shared_ptr<GameObject>& GetButton(unsigned char id);
	Ui::Text& GetButtonText(unsigned char id);
private:
	const Rendering::Color DEFAULT_COLOR {255, 255, 255, 255};
	void InitTitle(const std::string& title, int fontSize);
	void InitButtons(unsigned char numOfButtons, const Math::Vector2& startPos, const Math::Vector2& scale, int margin, int fontSize);
	std::shared_ptr<GameObject> _title;
	// unsigned char is used as id
	std::unordered_map<unsigned char, std::shared_ptr<GameObject>> _buttons;
};