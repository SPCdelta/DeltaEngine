#pragma once

#include "../Transform.hpp"
#include "../Rendering/Viewport.hpp"
#include <iostream>
#include <string>

class Camera
{
public:
	Camera(Transform& cameraTransform) 
		: transform{cameraTransform}
	{

	}

	void AddToPosition(const Math::Vector2 direction)
	{
		transform.position += direction;
	}

	void SetPosition(const Math::Vector2 position)
	{ 
		transform.position.Set(position);
	}

	void SetViewportData(ViewportData* viewportData)
	{
		_viewportData = viewportData;
		std::cout << (viewportData != nullptr ? "SetViewportData \n" : "Null \n");
		//std::cout << (viewportData != nullptr ? viewportData->unitPixelSize : -1);

	}

	Math::Vector2 ScreenToWorldPoint(const Math::Vector2 position){
		return ScreenToWorldPoint(position.GetX(), position.GetY());
	}

	Math::Vector2 ScreenToWorldPoint(int screenX, int screenY)
	{
		//_viewportData;
		GetunitPixelSize();
		std::cout << (_viewportData != nullptr ? "ScreenToWorldPoint \n" : "Nullptr \n");

		//std::cout << _viewportData->unitPixelSize;
		//std::cout << transform.position.GetX();
		//std::cout << transform.position.GetY();
		//std::cout << _viewportData->height;

		return 
		{ 
			static_cast<float>(screenX) / static_cast<float>(_viewportData->unitPixelSize) + transform.position.GetX(),
			static_cast<float>(-screenY + _viewportData->height) / static_cast<float>(_viewportData->unitPixelSize) + transform.position.GetY()
		};
	}

	int GetunitPixelSize(){
		return _viewportData->unitPixelSize;
	}

	Transform& transform;

private:
	ViewportData* _viewportData = nullptr;
};