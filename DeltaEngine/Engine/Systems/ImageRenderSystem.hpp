#pragma once

#include "../Ecs/Registry.hpp"

#include "../Window.hpp"
#include "../UI/Image.hpp"

class ImageRenderSystem : public ecs::System<Transform, Image>
{
public:
	ImageRenderSystem(ecs::View<Transform, Image> view)
		: ecs::System<Transform, Image>(view),
		  _window(nullptr),
		  _viewportData(nullptr)
	{

	}

	void SetWindow(Window* window) { _window = window; }

	void SetViewportData(ViewportData* viewportData)
	{
		_viewportData = viewportData;
	}

	void Update()
	{
		for (ecs::EntityId entityId : _view)
		{
			Image& image = _view.get<Image>(entityId);
			Transform& transform = _view.get<Transform>(entityId);

			image.Render(_window->GetRenderer(), *_viewportData, transform);
		}
	}

private:
	Window* _window;
	ViewportData* _viewportData;
};