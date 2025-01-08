#pragma once

#include <iostream>
#include <string>

#include "Font.hpp"
#include "../Core/Math/Point.hpp"
#include "../Rendering/Renderables/TextRenderable.hpp"

namespace Ui
{
	constexpr int DEFAULT_FONT_SIZE = 16;

	class Text : public TextRenderable
	{
	public:
		Text(const std::string& text, const std::string& fontName, int fontSize, const Rendering::Color& color);
		~Text();

		Text(const Text& other);
		Text& operator=(const Text& other);
		Text(Text&& other) noexcept;
		Text& operator=(Text&& other) noexcept;

		void Render(Rendering::Renderer* renderer, const Transform& transform);

		const std::string& GetText() const;
		void SetText(const std::string& text);

		void SetBackground(Rendering::Color color);
		void SetColor(const Rendering::Color& color);

		Font::Font* GetFont() const;
		void SetFont(const std::string& fontName);

		void SetFontSize(int size);
		int GetFontSize() const;
	
		void AddPosition(const Math::Vector2& position);
		void SetPosition(const Math::Vector2& position);	
		const Math::Vector2& GetPosition() const;

	private:
		std::string _text;
		std::string _fontName;
		Font::Font* _font;
		int _fontSize;

		Rendering::Color _color;
		bool _background = false;
		Rendering::Color _backgroundColor;

		Math::Vector2 _position;
	};
}  // namespace Ui
