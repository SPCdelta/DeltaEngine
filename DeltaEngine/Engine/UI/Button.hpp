#pragma once

#include "../Core/Math/Vector2.hpp"
#include "../Core/Math/Point.hpp"
#include "../Input/DeltaInputs.hpp"
#include "../Input/InputManager.hpp"

using namespace Math;

namespace Ui
{
class Button
{
   public:
	Button(const Vector2& position, const Vector2& scale) : _position{position}, _scale{scale} {}
	void SetOnLeftMouseClick(void (*func)());

   private:
	Vector2 _position;
	Vector2 _scale;
};
}  // namespace Ui
