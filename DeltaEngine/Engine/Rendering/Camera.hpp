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

	}

	Math::Vector2 ToWorldGrid(const Math::Point position){
		int pxUnit = GetunitPixelSize();
		const Math::Vector2 pos = ScreenToWorldPoint(position.GetX(), position.GetY());

		float addX = 0.0f;
		float addY = 0.0f;
		if (pos.GetX() < 0.0f)
			addX = -1.0f;
		if (pos.GetY() < 0.0f)
			addY = -1.0f;
	
		return {
			static_cast<int>(pos.GetX() + addX),
			static_cast<int>(pos.GetY() + addY)
		};

	}

	Math::Vector2 ScreenToWorldPoint(const Math::Point position){
		return ScreenToWorldPoint(static_cast<float>(position.GetX()), static_cast<float>(position.GetY()));
	}

	Math::Vector2 ScreenToWorldPoint(float screenX, float screenY)
	{
		return {
			screenX / static_cast<float>(_viewportData->unitPixelSize) + transform.position.GetX(),
			static_cast<float>(static_cast<float>(_viewportData->height) - screenY) / static_cast<float>(_viewportData->unitPixelSize) + transform.position.GetY()
		};
	}

	int GetunitPixelSize(){
		return _viewportData->unitPixelSize;
	}

	Transform& transform;

private:
	ViewportData* _viewportData = nullptr;
};