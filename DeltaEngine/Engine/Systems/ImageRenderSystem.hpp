#pragma once

#include "../Ecs/Registry.hpp"

#include "../Window.hpp"
#include "../UI/Image.hpp"
#include "../UI/Text.hpp"

class ImageRenderSystem : public ecs::System<Transform, Ui::Image>
{
public:
	ImageRenderSystem(ecs::View<Transform, Ui::Image> view)
	 : ecs::System<Transform, Ui::Image>(view),
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
			Ui::Image& image = _view.get<Ui::Image>(entityId);
			Transform& transform = _view.get<Transform>(entityId);
			image.SetColor(image.GetColor());
			image.Render(_window->GetRenderer(), *_viewportData, transform);
		}
	}

private:
	Window* _window;
	ViewportData* _viewportData;
};