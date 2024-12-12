#pragma once
#include "../../Core/Math/MathUtils.hpp"
#include "../../Rendering/Sprite.hpp"

class SnapToGridBrush
{
public:

	SnapToGridBrush(Transform& transform, Sprite* sprite, Camera* camera, const std::string& category = "UI") :
		_camera{camera}, _transform{transform}, _category{category}, _sprite{ sprite }
	{
		_sprite->SetVisible(false);		
	}

	void activate(std::function<void()> func){
		int pxUnit = _camera->GetunitPixelSize();
		
		_inputLocations.push_back(InputManager::onMouseMove(
			[this, pxUnit, func](Input& e)
			{

				int posX = e.mouseX - e.mouseX % pxUnit;
				int posY = e.mouseY - e.mouseY % pxUnit;

				Math::Vector2 mouseToWorldPos{ _camera->ScreenToWorldPoint({posX, posY + pxUnit}) };
				_transform.position.Set(mouseToWorldPos);
				if (_pressed)
					func();

			}, _category
		));

		_inputLocations.push_back(InputManager::onMouseButtonDown(MouseButton::Left,
			[this, func](Input& e)
			{
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

	void SetSprite(const std::string& spriteName){
		_sprite->SetSprite(spriteName);
		_sprite->SetVisible(true);
	}


	void SetCategory(const std::string& category){
		_category = category;
	}

	void RemoveOnKey(Key key, std::function<void()> func){
		_inputLocations.push_back(InputManager::onKeyPressed(key, [this, func](Input& e){
				//if (bingDragged)
					func();
			
			}, _category));
	}

	~SnapToGridBrush()
	{
		CleanUp();
	}

private:
	std::vector<InputLocation> _inputLocations;
	
	Camera* _camera;
	Transform& _transform;
	std::string _category;

	Sprite* _sprite;
	bool _pressed = false;
	
	void CleanUp(const std::string& category = "") {
		auto& inputM = InputManager::GetInstance();
		for (auto& input : _inputLocations)
		{
			inputM.remove(input);
		}
		_inputLocations.clear();
	}
	
};