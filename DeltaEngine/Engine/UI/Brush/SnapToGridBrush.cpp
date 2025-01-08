#include "SnapToGridBrush.hpp"

SnapToGridBrush::SnapToGridBrush(Transform& transform, Sprite* sprite, Camera* camera, std::function<void(Transform&, Sprite*)> func, const std::string& category) 
	: _camera{camera}, 
	  _transform{transform}, 
	  _category{category}, 
	  _sprite{ sprite }, 
	  _func{ func }
{
	_sprite->SetVisible(false);
	_sprite->SetBorder(2);
	_sprite->SetBorderColor({ 100, 0, 0 });
	_sprite->SetLayer(Layer::EngineLayer);
	int pxUnit = _camera->GetunitPixelSize();
		
	_inputListeners.Add(InputManager::onMouseMove(
		[this, pxUnit](Input& e)
		{
			if (!_isActive)
				return;

			_transform.position.Set(_camera->ToWorldGrid({ e.mouseX, e.mouseY }));
			if (_pressed)
				_func(_transform, _sprite);

		}, _category
	));

	_inputListeners.Add(InputManager::onMouseButtonDown(MouseButton::Left,
		[this](Input& e)
		{
			if (!_isActive || !Math::MathUtils::IsPointWithinRect({ e.mouseX, e.mouseY }, _screenViewPort.position, _screenViewPort.scale))
				return;

			_func(_transform, _sprite);
			_pressed = true;
		}, _category
	));

	_inputListeners.Add(InputManager::onMouseButtonUp(MouseButton::Left,
		[this](Input& e)
		{
			_pressed = false;
		}, _category
	));
}

void SnapToGridBrush::NotifyTransform()
{
	if (!_pressed)
		return;
		
	_transform.position.Set(_camera->ToWorldGrid(InputManager::GetMousePosition()));
	_func(_transform, _sprite);
}

void SnapToGridBrush::SetSprite(const std::string& spriteName)
{
	_isActive = true;
	_transform.position.Set(_camera->ToWorldGrid(InputManager::GetMousePosition()));
	_sprite->SetSprite(spriteName);
	_sprite->SetVisible(true);
}

void SnapToGridBrush::SetCategory(const std::string& category)
{
	_category = category;
}

void SnapToGridBrush::RemoveOnKey(Key key)
{
	_inputListeners.Add(InputManager::onKeyPressed(key, [this](Input& e)
	{
		_isActive = false;
		_sprite->SetVisible(false);
	}, _category));
}

void SnapToGridBrush::SetCanvas(Transform screenViewPort_)
{
	_screenViewPort = screenViewPort_;
}

void SnapToGridBrush::MouseToCanvase(Math::Point& mouse)
{
	if (static_cast<float>(mouse.GetX()) < _screenViewPort.position.GetX())
		mouse.SetX(static_cast<int>(_screenViewPort.position.GetX()));

	if (static_cast<float>(mouse.GetY()) < _screenViewPort.position.GetY())
		mouse.SetY(static_cast<int>(_screenViewPort.position.GetY()));

	if (static_cast<float>(mouse.GetX()) > _screenViewPort.scale.GetX())
		mouse.SetX(static_cast<int>(_screenViewPort.scale.GetX()));

	if (static_cast<float>(mouse.GetY()) > _screenViewPort.scale.GetY())
		mouse.SetY(static_cast<int>(_screenViewPort.scale.GetY()));
}