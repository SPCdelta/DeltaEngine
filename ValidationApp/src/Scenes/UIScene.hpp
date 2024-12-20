#pragma once

#include "Engine/Delta.hpp"
#include "../Views/WindowView.hpp"
#include "../Views/ListView.hpp"
#include "../Views/ListViewItem.hpp"

class UIScene : public Scene
{
public:
	UIScene(const std::string& name)
		: Scene(name) {}

	void OnStart() override
	{
		auto listItem = ListViewItem{ *this, "player", "goblin", "Hello World!", {200, 200} };
		listItem.Show();
		//auto list = ListView{ *this, "goblin", {}, 5, listItem };
		//WindowView wv{ *this, "goblin", {100, 100,}, list, {50, 50} };
	}
};