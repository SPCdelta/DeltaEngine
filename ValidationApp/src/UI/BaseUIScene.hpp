#pragma once

#include <Engine/Delta.hpp>

#include "UIFactory.hpp"

class BaseUIScene : public Scene
{
public:
	BaseUIScene(const std::string& name, const std::string& title, const std::string& previousSceneName);

	void OnStart() override;

	Math::Vector2 GetContentOffset();
	Math::Vector2 GetBarOffset();

private:
	static constexpr float SideMargin = 64.0f;

	std::string _titleText;
	std::string _previousSceneName;

	GameObject* _title = nullptr;
	GameObject* _backButton = nullptr;
};
