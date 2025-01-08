#pragma once

#include "../Ecs/Registry.hpp"
#include "../UI/Text.hpp"
#include "../Window.hpp"
#include "../Transform.hpp"

class TextRenderSystem : public ecs::System<Transform, Ui::Text>
{
public:
	TextRenderSystem(ecs::View<Transform, Ui::Text> view);

	void SetWindow(Window* window);
	void SetViewportData(ViewportData* viewportData);

	void OnStart();
	void Update();

private:
	Window* _window;
	ViewportData* _viewportData;
};