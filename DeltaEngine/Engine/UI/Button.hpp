#pragma once

#include "../Input/DeltaInputs.hpp"
#include "../Input/InputHandler.hpp"
#include "../Transform.hpp"

#include <functional>
#include <memory>
#include <vector>

using namespace Math;

namespace Ui
{
	class Button
	{
	public:
		Button(Transform* transform);

		void SetOnLeftMouseClick(std::function<void()> func, const std::string& category);
		void SetOnMouseHover(std::function<void()> func);
		void SetOnMousePressed(std::function<void()> func, const std::string& category);

	private:
		InputHandler _inputListeners;
		bool _pressed = false;
		Transform* _transform;
	};
}  // namespace Ui
