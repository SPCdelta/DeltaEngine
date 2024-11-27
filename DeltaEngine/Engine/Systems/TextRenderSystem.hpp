#pragma once

#include "../Ecs/Registry.hpp"

#include "../UI/Text.hpp"
#include "../Window.hpp"
#include "../Transform.hpp"

class TextRenderSystem : public ecs::System<Transform, Ui::Text>
{
   public:
	TextRenderSystem(ecs::View<Transform, Ui::Text> view) : ecs::System<Transform, Ui::Text>(view), _window(nullptr),
		  _viewportData(nullptr) {}

	void SetWindow(Window* window) { _window = window; }

	void SetViewportData(ViewportData* viewportData) { _viewportData = viewportData; }

	void OnStart()
	{
		for (ecs::EntityId entityId : _view)
		{
			Ui::Text& text = _view.get<Ui::Text>(entityId);
			Transform& transform = _view.get<Transform>(entityId);
			text.SetFontSize(transform.scale.Magnitude()); // Set font size here so we don't continuously keep changing the size.
			text.Render(_window->GetRenderer(), transform);
		}
	}

	void Update()
	{
		for (ecs::EntityId entityId : _view)
		{
			Ui::Text& text = _view.get<Ui::Text>(entityId);
			Transform& transform = _view.get<Transform>(entityId);
			text.Render(_window->GetRenderer(), transform);
		}
	}

   private:
	Window* _window;
	ViewportData* _viewportData;
};