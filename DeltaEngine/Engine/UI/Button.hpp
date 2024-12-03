#pragma once

#include "../Core/Math/Vector2.hpp"
#include "../Core/Math/Point.hpp"
#include "../Input/DeltaInputs.hpp"
#include "../Input/InputManager.hpp"
#include <functional>

using namespace Math;

namespace Ui
{
class Button
{
   public:
	   // Het actieve gebied waarop je kunt klikken op button is gelijk aan de grootte van de gameObject waaraan die is toegevoegd.
	Button(const Vector2& position, const Vector2& scale) : _position{position}, _scale{scale} {}
	void SetOnLeftMouseClick(std::function<void()> func, const std::string& category);
	void SetPosition(const Vector2& scale);
	void SetScale(const Vector2& scale);

   private:
	std::function<void()> _func;
	Vector2 _position;
	Vector2 _scale;
};
}  // namespace Ui
