#include "ShopScene.hpp"
#include "../Views/ShopView.hpp"

ShopScene::ShopScene(const std::string& sceneName) : Scene(sceneName) {
	ShopView shopView{*this, "Shop"};
}
