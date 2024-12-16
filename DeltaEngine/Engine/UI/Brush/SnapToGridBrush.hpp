#pragma once
#include "../../Core/Math/MathUtils.hpp"
#include "../../Rendering/Sprite.hpp"
#include "../../Core/Events/EventDispatcher.hpp"

#include <algorithm>

class SnapToGridBrush
{
public:

	SnapToGridBrush(Transform& transform, Sprite* sprite, Camera* camera, std::function<void(Transform&, Sprite*)> func, const std::string& category = "UI") :
		_camera{camera}, _transform{transform}, _category{category}, _sprite{ sprite }, _func{ func }
	{
		_sprite->SetVisible(false);
		_sprite->SetBorder(2);
		_sprite->SetBorderColor({ 100, 0, 0 });
		_sprite->SetLayer(Layer::EngineLayer);
		int pxUnit = _camera->GetunitPixelSize();
		
		_inputLocations.push_back(InputManager::onMouseMove(
			[this, pxUnit](Input& e)
			{
				if (!_isActive)
					return;

				_transform.position.Set(_camera->ToWorldGrid({ e.mouseX, e.mouseY }));
				if (_pressed)
					_func(_transform, _sprite);

			}, _category
		));

		_inputLocations.push_back(InputManager::onMouseButtonDown(MouseButton::Left,
			[this](Input& e)
			{
				if (!_isActive || !Math::MathUtils::IsPointWithinRect({ e.mouseX, e.mouseY }, _screenViewPort.position, _screenViewPort.scale))
					return;


				_func(_transform, _sprite);
				_pressed = true;
			}, _category
		));

		_inputLocations.push_back(InputManager::onMouseButtonUp(MouseButton::Left,
			[this](Input& e)
			{
				_pressed = false;
			}, _category
		));
	}

	void NotifyTransform(){
		if (!_pressed)
			return;
		
		_transform.position.Set(_camera->ToWorldGrid(InputManager::GetMousePosition()));
		_func(_transform, _sprite);
	}

	void SetSprite(const std::string& spriteName){
		_isActive = true;
		_transform.position.Set(_camera->ToWorldGrid(InputManager::GetMousePosition()));
		_sprite->SetSprite(spriteName);
		_sprite->SetVisible(true);
	}


	void SetCategory(const std::string& category){
		_category = category;
	}

	void RemoveOnKey(Key key){
		_inputLocations.push_back(InputManager::onKeyPressed(key, [this](Input& e){
				_isActive = false;
				_sprite->SetVisible(false);
			}, _category));
	}

	void SetCanves(Transform screenViewPort_){
		_screenViewPort = screenViewPort_;
	}

	~SnapToGridBrush()
	{
		CleanUp();
	}

private:
	void MouseToCanvase(Math::Point& mouse){
		if (static_cast<float>(mouse.GetX()) < _screenViewPort.position.GetX())
			mouse.SetX(static_cast<int>(_screenViewPort.position.GetX()));
		
		if (static_cast<float>(mouse.GetY()) < _screenViewPort.position.GetY())
			mouse.SetY(static_cast<int>(_screenViewPort.position.GetY()));
		
		if (static_cast<float>(mouse.GetX()) > _screenViewPort.scale.GetX())
			mouse.SetX(static_cast<int>(_screenViewPort.scale.GetX()));
		
		if (static_cast<float>(mouse.GetY()) > _screenViewPort.scale.GetY())
			mouse.SetY(static_cast<int>(_screenViewPort.scale.GetY()));

	}

	std::vector<InputLocation> _inputLocations;
	
	Camera* _camera;
	Transform& _transform;
	Transform _screenViewPort;

	std::string _category;

	Sprite* _sprite;
	bool _pressed = false;
	bool _isActive = false;
	std::function<void(Transform&, Sprite*)> _func;

	
	void CleanUp(const std::string& category = "") {
		auto& inputM = InputManager::GetInstance();
		for (auto& input : _inputLocations)
		{
			inputM.remove(input);
		}
		_inputLocations.clear();
	}
	
};