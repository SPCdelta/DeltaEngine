#include "TextRenderSystem.hpp"

TextRenderSystem::TextRenderSystem(ecs::View<Transform, Ui::Text> view) 
	: ecs::System<Transform, Ui::Text>(view), 
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
	for (ecs::EntityId entityId : _view)
	{
		Ui::Text& text = _view.get<Ui::Text>(entityId);
		Transform& transform = _view.get<Transform>(entityId);
		text.Render(_window->GetRenderer(), transform);
	}
}

void TextRenderSystem::Update()
{
	for (ecs::EntityId entityId : _view)
	{
		Ui::Text& text = _view.get<Ui::Text>(entityId);
		Transform& transform = _view.get<Transform>(entityId);
		text.Render(_window->GetRenderer(), transform);
	}
}