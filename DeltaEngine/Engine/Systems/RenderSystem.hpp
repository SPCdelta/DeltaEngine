#pragma once

#include "../Ecs/Registry.hpp"
#include "../Ecs/Include.hpp"

#include "../Window.hpp"
#include "../Rendering/Sprite.hpp"

class RenderSystem : public ecs::System<Transform, Sprite>
{
public:
	RenderSystem(ecs::Registry& reg, Camera* camera); 

	Window* GetWindow();
	void SetWindow(Window* window);
	void SetViewportData(ViewportData* viewportData);

	void OnStart();
	void Update();

private:
	Window* _window;
	ViewportData* _viewportData;
	Camera* _camera;
};