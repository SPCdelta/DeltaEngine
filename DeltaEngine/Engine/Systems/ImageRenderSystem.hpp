#pragma once

#include "../Ecs/Registry.hpp"
#include "../Ecs/Include.hpp"

#include "../Window.hpp"
#include "../UI/Image.hpp"
#include "../UI/Text.hpp"

class ImageRenderSystem : public ecs::System<Transform, Ui::Image>
{
public:
	ImageRenderSystem(ecs::Registry& reg);

	void SetWindow(Window* window);
	void SetViewportData(ViewportData* viewportData);

	void Update();

private:
	Window* _window;
	ViewportData* _viewportData;
};