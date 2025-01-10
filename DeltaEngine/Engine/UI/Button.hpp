#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "../Input/DeltaInputs.hpp"
#include "../Input/InputHandler.hpp"
#include "../Transform.hpp"
#include "../Input/JLifetimeManager.hpp"

using namespace Math;

namespace Ui
{
	class Button
	{
	public:
		Button(Transform* transform) : _transform{ transform }{}
		void SetOnLeftMouseClick(std::function<void()> func, const std::string& category);
		void SetOnMouseHover(std::function<void()> func);
		void SetOnMousePressed(std::function<void()> func, const std::string& category);

	private:
		InputHandler _inputListeners;
		bool _pressed = false;
		Transform* _transform;
		JInputLifetimeManager _inputs;
		
	};
}  // namespace Ui
