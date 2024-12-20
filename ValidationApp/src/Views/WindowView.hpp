#pragma once

#include "Engine/Delta.hpp"
#include "IView.hpp"

class WindowView : public IView
{
public:
	WindowView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, IView& body, const Math::Vector2& margin);
	const Math::Vector2& GetSize() const override;
	void SetCenter() override;
private:
	void SetBody(IView& body);
	const std::string WINDOW_FRAME_SPRITENAME = "window_frame";
	std::shared_ptr<GameObject> _window;
	Math::Vector2 _margin;
};

