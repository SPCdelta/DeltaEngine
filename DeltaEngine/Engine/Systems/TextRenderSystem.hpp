#pragma once

#include "../Ecs/Include.hpp"

#include "../UI/Text.hpp"
#include "../Window.hpp"
#include "../Transform.hpp"

class TextRenderSystem : public ecs::System<Transform, Ui::Text>
{
   public:
	TextRenderSystem(ecs::Registry& reg) 
		: ecs::System<Transform, Ui::Text>(reg), _window(nullptr),
		  _viewportData(nullptr) {}

	void SetWindow(Window* window) { _window = window; }

	void SetViewportData(ViewportData* viewportData) { _viewportData = viewportData; }

	void OnStart()
	{
		RefreshView();
		for (ecs::EntityId entityId : _view)
		{
			Ui::Text& text = _view.get<Ui::Text>(entityId);
			Transform& transform = _view.get<Transform>(entityId);
			text.Render(_window->GetRenderer(), transform);
		}
	}

	void Update()
	{
		RefreshView();
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