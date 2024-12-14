#pragma once

#include "../../Core/Math/Vector2.hpp"

#include "../ResourceManager.hpp"
#include "../Rendering.hpp"
#include "../Animator.hpp"
#include "../AnimationSheet.hpp"
#include "../Viewport.hpp"
#include "../Camera.hpp"
#include "../Layer.hpp"
#include <iostream>

#include <string>

class Renderable
{
public:
	Renderable(){};

	Renderable(const Renderable& other);
	Renderable& operator=(const Renderable& other);

	Renderable(Renderable&& other) noexcept;
	Renderable& operator=(Renderable&& other) noexcept;

	Rendering::Color GetColor() const;
	void SetColor(Rendering::Color newColor);

	void SetFlipX(bool flip) { flipX = flip; };
	void SetFlipY(bool flip) { flipY = flip; };

	Layer GetLayer() const { return _layer; };
	void SetLayer(Layer layer) { _layer = layer; };

	void SetBorder(uint16_t borderThickness_) { borderThickness = borderThickness_; };
	void SetBorderColor(Rendering::Color borderColor_) { borderColor = borderColor_; };
	void RemoveBorder() { borderThickness = 0; };

protected:
	void RenderBorder(Rendering::Renderer* renderer, Rendering::Rect& borderRect);

	Rendering::Color color{Rendering::Color(255, 255, 255, 255)}; //If this is not White it will not show the textures

	bool flipX{false};
	bool flipY{false};

	uint16_t borderThickness{0};
	Rendering::Color borderColor{ Rendering::Color(0,0,0) };

	Layer _layer{ Layer::Default };
};