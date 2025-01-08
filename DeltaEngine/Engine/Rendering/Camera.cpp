#include "Camera.hpp"

Camera::Camera(Transform& cameraTransform) 
	: transform{cameraTransform} 
{

}

void Camera::AddToPosition(const Math::Vector2 direction)
{
	transform.position += direction;
}

void Camera::SetPosition(const Math::Vector2 position)
{
	transform.position.Set(position);
}

void Camera::SetViewportData(ViewportData* viewportData)
{
	_viewportData = viewportData;
}

Math::Vector2 Camera::ToWorldGrid(const Math::Point& position)
{
	int pxUnit = GetunitPixelSize();
	const Math::Vector2 pos = ScreenToWorldPoint(position);

	float addX = 0.0f;
	float addY = 0.0f;

	if (pos.GetX() < 0.0f)
		addX = -1.0f;
	if (pos.GetY() < 0.0f)
		addY = -1.0f;

	return {static_cast<int>(pos.GetX() + addX),static_cast<int>(pos.GetY() + addY)};
}

Math::Vector2 Camera::ScreenToWorldPoint(const Math::Point position)
{
	return ScreenToWorldPoint(static_cast<float>(position.GetX()), static_cast<float>(position.GetY()));
}

/// <summary>
/// <param name="screenX">X coordinate of screen</param>
/// <param name="screenY">Y coordinate of screen</param>
/// <returns></returns>
/// </summary>
Math::Vector2 Camera::ScreenToWorldPoint(float screenX, float screenY)
{
	return 
	{
		(screenX - (static_cast<float>(_viewportData->width) / 2.0f)) / static_cast<float>(_viewportData->unitPixelSize) + transform.position.GetX(),
		static_cast<float>(static_cast<float>(_viewportData->height / 2.0f) - (screenY)) / static_cast<float>(_viewportData->unitPixelSize) + transform.position.GetY()
	};
}

int Camera::GetunitPixelSize()
{
	return _viewportData->unitPixelSize;
}