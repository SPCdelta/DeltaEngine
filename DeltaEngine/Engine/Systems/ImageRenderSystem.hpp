#pragma once

#include "../Ecs/Include.hpp"

#include "../Window.hpp"
#include "../UI/Image.hpp"
#include "../UI/Text.hpp"

class ImageRenderSystem : public ecs::System<Transform, Ui::Image>
{
public:
	ImageRenderSystem(ecs::Registry& reg)
	 : ecs::System<Transform, Ui::Image>(reg),
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
		RefreshView();
		// Collect entities and sort by layer
		std::vector<ecs::EntityId> entities(_view.begin(), _view.end());
		std::sort(entities.begin(), entities.end(), [this](ecs::EntityId a, ecs::EntityId b) 
		{
			int layerA = static_cast<int>(_view.get<Ui::Image>(a).GetLayer());
			int layerB = static_cast<int>(_view.get<Ui::Image>(b).GetLayer());
			return layerA < layerB; // Lower layers render first
		});

		for (ecs::EntityId entityId : entities)
		{
			Ui::Image& image = _view.get<Ui::Image>(entityId);
			Transform& transform = _view.get<Transform>(entityId);

			if (image.GetVisible())
			{
				image.Render(_window->GetRenderer(), *_viewportData, transform);
			}
		}
	}

private:
	Window* _window;
	ViewportData* _viewportData;
};