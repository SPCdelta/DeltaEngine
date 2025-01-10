#include "TextRenderSystem.hpp"

TextRenderSystem::TextRenderSystem(ecs::Registry& reg) 
	: ecs::System<Transform, Ui::Text>(reg), 
	  _window(nullptr),
	  _viewportData(nullptr) 
{
	
}

void TextRenderSystem::SetWindow(Window* window) 
{ 
	_window = window; 
}

void TextRenderSystem::SetViewportData(ViewportData* viewportData)
{
	_viewportData = viewportData;
}

void TextRenderSystem::OnStart()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		Ui::Text& text = _view.get<Ui::Text>(entityId);
		Transform& transform = _view.get<Transform>(entityId);
		text.Render(_window->GetRenderer(), transform);
	}
}

void TextRenderSystem::Update()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		Ui::Text& text = _view.get<Ui::Text>(entityId);
		Transform& transform = _view.get<Transform>(entityId);
		text.Render(_window->GetRenderer(), transform);
	}
}