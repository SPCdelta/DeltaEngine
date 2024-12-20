#pragma once

#include "IView.hpp"

// ListViewItem is an UI element that contains a background, icon image and some text.
class ListViewItem : public IView
{
public:
	ListViewItem(Scene& scene, const std::string& bgSpriteName, const std::string& spriteName, const std::string& fontName, const std::string& text, const Math::Vector2& scale);
	void Show();
	const Math::Vector2& GetSize() const override;
	void SetPosition(const Math::Vector2& pos) override;

private:
	std::shared_ptr<GameObject> _item;
	std::string _bgSpriteName;
	std::string _spriteName;
	std::string _text;
};

