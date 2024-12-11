#pragma once
#include "../Core/Math/MathUtils.hpp"


class SnapToGridDraggable
{
public:

	SnapToGridDraggable(Camera* camera, Transform* transform, const std::string& category = "UI") : _camera{camera}, _transform{transform}, _category{category}
	{}

	void activate(const std::string& category, std::function<void()> func){
		int pxUnit = _camera->GetunitPixelSize();
		CleanUp(_category);
		_category = category;

		_inputLocations.push_back(InputManager::onMouseMove(
			[this, pxUnit](Input& e)
			{
				if (!bingDragged)
					return;

				int posX = e.mouseX - e.mouseX % pxUnit;
				int posY = e.mouseY - e.mouseY % pxUnit;

				Math::Vector2 mouseToWorldPos{ _camera->ScreenToWorldPoint({posX, posY + pxUnit}) };
				_transform->position.Set(mouseToWorldPos);
			}, category
		));

		_inputLocations.push_back(InputManager::onMouseButtonDown(MouseButton::Left,
			[this, func](Input& e)
			{
				if (bingDragged)
					return;
				auto mousevector = _camera->ScreenToWorldPoint({e.mouseX, e.mouseY});

				if (!Math::MathUtils::IsVector2WithinRect(mousevector, _transform->position, _transform->scale))
					return;

				bingDragged = true;
				func();
			}, _category
		));

		_inputLocations.push_back(InputManager::onMouseButtonUp(MouseButton::Left,
			[this](Input& e)
			{
				bingDragged = false;
			}, _category
		));
	}

	void CleanUp(const std::string& category = ""){
		auto& inputM = InputManager::GetInstance();
		for (auto& input : _inputLocations)
		{
			if (category.empty() || category == input.category)
				inputM.remove(input);
		}
		_inputLocations.clear();
	}

	bool isBingDragged(){
		return bingDragged;
	}

	void SetCategory(const std::string& category){
		_category = category;
	}

	void RemoveOnKey(Key key, std::function<void()> func){
		_inputLocations.push_back(InputManager::onKeyPressed(key, [this, func](Input& e){
				if (bingDragged)
					func();
			
			}, _category));
	}

	void SetDraggeble(bool value){
		bingDragged = value;
	}

	~SnapToGridDraggable()
	{
		CleanUp();
	}

private:
	Camera* _camera;
	Transform* _transform;
	std::string _category;
	bool bingDragged = true;

	std::vector<InputLocation> _inputLocations;
};