#pragma once

#include "../Ecs/Registry.hpp"
#include "../Window.hpp"
#include "../UI/Image.hpp"
#include "../UI/Text.hpp"

class ImageRenderSystem : public ecs::System<Transform, Ui::Image>
{
public:
	ImageRenderSystem(ecs::View<Transform, Ui::Image> view);

	void SetWindow(Window* window);
	void SetViewportData(ViewportData* viewportData);

	void Update();

private:
	Window* _window;
	ViewportData* _viewportData;
};