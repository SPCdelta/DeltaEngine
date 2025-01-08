#include "ImageRenderSystem.hpp"

ImageRenderSystem::ImageRenderSystem(ecs::View<Transform, Ui::Image> view)
	: ecs::System<Transform, Ui::Image>(view),
	  _window(nullptr),
	  _viewportData(nullptr)
{

}

void ImageRenderSystem::SetWindow(Window* window)
{
	_window = window;
}

void ImageRenderSystem::SetViewportData(ViewportData* viewportData)
{
	_viewportData = viewportData;
}

void ImageRenderSystem::Update()
{
	for (ecs::EntityId entityId : _view)
	{
		Ui::Image& image = _view.get<Ui::Image>(entityId);
		Transform& transform = _view.get<Transform>(entityId);
		image.Render(_window->GetRenderer(), *_viewportData, transform);
	}
}