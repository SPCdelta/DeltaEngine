#pragma once
#include <iostream>
#include <string>
#include "Font.hpp"
#include "../Core/Math/Point.hpp"
#include "../Rendering/Renderables/TextRenderable.hpp"

namespace Ui
{
class Text : public TextRenderable
{
   public:
	Text(const std::string& text, const std::string& fontName, int fontSize, const Rendering::Color& color);
	Text(const Text& other);
	Text& operator=(const Text& other);
	Text(Text&& other) noexcept;
	Text& operator=(Text&& other) noexcept;
	~Text();
	void Render(Rendering::Renderer* renderer, const Transform& transform);
	void SetText(const std::string& text);
	void SetBackground(Rendering::Color color);
	void SetFont(const std::string& fontName);
	const std::string& GetText() const;
	void SetFontSize(int size);
	int GetFontSize() const;
	Font::Font* GetFont() const;
	void AddPosition(const Math::Vector2& position);
	void SetPosition(const Math::Vector2& position);
	void SetColor(const Rendering::Color& color);
	const Math::Vector2& GetPosition() const;
	Transform GetTransform();

   private:
	std::string _text;
	std::string _fontName;
	Font::Font* _font;
	int _fontSize;
	Rendering::Color _color;
	bool _background = false;
	Rendering::Color _backgroundColor;
	Math::Vector2 _position;

	const int defaultFontSize = 16;
};
}  // namespace Ui
