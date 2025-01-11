#pragma once

#include <vector>
#include <string>

enum class Layer : int
{
	Background = 0,
	Button,
	Floor,
	Items,
	Wall,
	Default,
	Player,
	Projectiles,
	Particles,
	Foreground,
	EngineLayer
};

class LayerHelper
{
public:
	static Layer GetLowest();
	static Layer GetHighest();
	static bool InLayers(int layer);

	static int GetInt(Layer layer);
	static std::string GetString(Layer layer);

	static Layer GetLayer(int layer);
	static std::vector<Layer> GetAllLayer();
};
