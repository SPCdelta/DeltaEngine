#pragma once

#include <iostream>

#include "Rendering/Rendering.hpp"
#include "Rendering/Viewport.hpp"
#include "Rendering/ResourceManager.hpp"

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void Close();
	bool ShouldWindowClose();

	void Update();

	void SetTitle(const char* title);
	const char* GetTitle() const;

	Rendering::Renderer* GetRenderer();
	operator Rendering::Window*() const;

	void SetViewportSize(int width, int height);
	void SetViewportPos(int x, int y);
	void SetUnitPixelSize(int unitPixelSize);
	ViewportData& GetViewport();
	void RenderViewport(Rendering::UnsignInt8 r, Rendering::UnsignInt8 g, Rendering::UnsignInt8 b, Rendering::UnsignInt8 a);

private:
	Rendering::Window* _window;
	Rendering::Renderer* _renderer;

	ViewportData _viewportData{};

	bool _shouldWindowClose{false};
};