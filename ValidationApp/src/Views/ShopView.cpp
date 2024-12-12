#include "ShopView.hpp"

ShopView::ShopView(Scene& scene, std::string font) : IView(scene, font) {
	LoadImage();
}

void ShopView::SetButtonOnLeftMouseClick(std::function<void()> func, const std::string& catergory)
{
	_button->GetComponent<Ui::Button>().SetOnLeftMouseClick(func, catergory);
}

void ShopView::SetButtonPosition(const Math::Vector2& pos) {
	_button->transform->position = pos;
}

void ShopView::LoadImage()
{
	//_shop = std::shared_ptr<GameObject>{
	//	_scene.Instantiate({{0.0f, 0.0f}, 0, {1280.0f, 720.0f}})};
	//_shop->AddComponent<Ui::Image>("shop2");

	_button = std::shared_ptr<GameObject>{
		_scene.Instantiate({{500.0f, 500.0f}, 0, {50.0f, 50.0f}})};

	_button->AddComponent<Ui::Image>("scroll")->SetLayer(Layer::Foreground);
	_button->AddComponent<Ui::Button>();
	_button->GetComponent<Ui::Button>().SetOnLeftMouseClick(
		[this]() { this->test(); }, "test");

}

void ShopView::test() {
	std::cout << "Ja ik doe het!" << std::endl;
}


