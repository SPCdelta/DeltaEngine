#pragma once

#include "../Core/Math/MathUtils.hpp"
#include "../Input/InputManager.hpp"
#include "../Input/InputHandler.hpp"
#include "../Transform.hpp"

namespace Ui
{
	class Scrollable
	{
	public:
		Scrollable(Transform* transform, std::function<void(int)> func);

	private:
		std::unique_ptr<InputListener> _scrollable;
	};
}