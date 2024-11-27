#pragma once

#include "../Ecs/Registry.hpp"

#include "../UI/Text.hpp"
#include "../Window.hpp"
#include "../Transform.hpp"

class TextRenderSystem : public ecs::System<Transform, Ui::Text>
{
   public:
	TextRenderSystem(ecs::View<Transform, Ui::Text> view)
		: ecs::System<Transform, Ui::Text>(view),
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
			Ui::Text& text = _view.get<Ui::Text>(entityId);
			Transform& transform = _view.get<Transform>(entityId);
			text.SetColor(text.GetColor());
			text.Render(_window->GetRenderer(), *_viewportData, transform);
		}
	}

   private:
	Window* _window;
	ViewportData* _viewportData;
};