#pragma once

#include "../Transform.hpp"
#include "../Rendering/Viewport.hpp"

#include <iostream>
#include <string>

class Camera
{
public:
	Camera(Transform& cameraTransform);

	void AddToPosition(const Math::Vector2 direction);
	void SetPosition(const Math::Vector2 position);

	void SetViewportData(ViewportData* viewportData);

	Math::Vector2 ToWorldGrid(const Math::Point& position);

	Math::Vector2 ScreenToWorldPoint(const Math::Point position);

	/// <summary>
	/// <param name="screenX">X coordinate of screen</param>
	/// <param name="screenY">Y coordinate of screen</param>
	/// <returns></returns>
	/// </summary>
	Math::Vector2 ScreenToWorldPoint(float screenX, float screenY);

	int GetunitPixelSize();

	Transform& transform;

private:
	ViewportData* _viewportData = nullptr;
};