#pragma once

#include "IView.hpp"

class ShopView : public IView
{
   public:
	ShopView(Scene& scene, std::string font);
	void SetButtonOnLeftMouseClick(std::function<void()> func, const std::string& catergory);
	void SetButtonText(const std::string& text);
	void SetButtonPosition(const Math::Vector2& pos);

   private:
	void LoadImage();
	void test();
	std::shared_ptr<GameObject> _shop;
	std::shared_ptr<GameObject> _button;
};
