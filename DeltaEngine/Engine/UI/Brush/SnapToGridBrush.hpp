#pragma once
#include "../../Core/Math/MathUtils.hpp"
#include "../../Rendering/Sprite.hpp"

#include <algorithm>

class SnapToGridBrush
{
public:

	SnapToGridBrush(Transform& transform, Sprite* sprite, Camera* camera, const std::string& category = "UI") :
		_camera{camera}, _transform{transform}, _category{category}, _sprite{ sprite }
	{
		_sprite->SetVisible(false);		
	}

	void activate(std::function<void(Transform&, Sprite*)> func){
		int pxUnit = _camera->GetunitPixelSize();
		
		_inputLocations.push_back(InputManager::onMouseMove(
			[this, pxUnit, func](Input& e)
			{
				_transform.position.Set(_camera->ToWorldGrid({e.mouseX, e.mouseY}));
				if (_pressed)
					func(_transform, _sprite);

			}, _category
		));

		_inputLocations.push_back(InputManager::onMouseButtonDown(MouseButton::Left,
			[this, func](Input& e)
			{
				func(_transform, _sprite);
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

	//void placeTile(std::map<Layer, std::vector<std::shared_ptr<GameObject>>>& tilesPerLayer){
	//	auto& vector = tilesPerLayer[_sprite->GetLayer()];
	//	
	//	auto it = std::find_if(vector.begin(), vector.end(), [this](GameObject& e) {
	//		if (e.transform->position == _transform.position){
	//			e.GetComponent<Sprite>().SetSprite(_sprite->GetSprite());
	//			return;	
	//		}
	//	});

	//	//if (it == vector.end())
	//		//vector.emplace_back(Instantiate({ {mousePos.GetX(), mousePos.GetY()}, 0.0f, {1.0f, 1.0f} }));;
	//}

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