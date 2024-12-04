#pragma once
#include <iostream>
#include <string>
#include "Font.hpp"
#include "../Core/Math/Point.hpp"
#include "../Rendering/Renderables/TextRenderable.h"

namespace Ui
{
class Text : public TextRenderable
{
   public:
	Text(const std::string& text, const std::string& path, const Rendering::Color& color);
	Text(const Text& other);
	Text& operator=(const Text& other);
	Text(Text&& other) noexcept;
	Text& operator=(Text&& other) noexcept;
	~Text();
	void Render(Rendering::Renderer* renderer, const Transform& transform);
	void SetText(const std::string& text);
	void SetFontSize(const size_t size);
	void SetPosition(const Math::Vector2& position);

   private:
	std::string _text;
	Font::Font* _font;
	Rendering::Color _color;
	Math::Vector2 _position;

	const int defaultFontSize = 16;
};
}  // namespace Ui
