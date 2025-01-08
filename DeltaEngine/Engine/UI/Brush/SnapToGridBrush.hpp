#pragma once

#include "../../Core/Math/MathUtils.hpp"
#include "../../Rendering/Sprite.hpp"
#include "../../Core/Events/EventDispatcher.hpp"
#include "../../Input/InputHandler.hpp"

#include <algorithm>

class SnapToGridBrush
{
public:
	SnapToGridBrush(Transform& transform, Sprite* sprite, Camera* camera, std::function<void(Transform&, Sprite*)> func, const std::string& category = "UI");

	void NotifyTransform();

	void SetSprite(const std::string& spriteName);
	void SetCategory(const std::string& category);
	void SetCanvas(Transform screenViewPort_);

	void RemoveOnKey(Key key);	

private:
	void MouseToCanvase(Math::Point& mouse);

	InputHandler _inputListeners;
	
	Camera* _camera;
	Transform& _transform;
	Transform _screenViewPort;

	std::string _category;

	Sprite* _sprite;
	bool _pressed = false;
	bool _isActive = false;

	std::function<void(Transform&, Sprite*)> _func;
};