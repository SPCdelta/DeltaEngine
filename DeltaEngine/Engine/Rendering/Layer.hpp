#pragma once

#include <vector>

enum class Layer : int
{
	Background = 0,
	Floor,
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
	static Layer GetLowest()
	{
		return Layer::Background;
	}

	static Layer GetHighest() 
	{
		return Layer::Foreground;
	}

	static bool InLayers(int layer)
	{
		int lowests = static_cast<int>(GetLowest());
		int heights = static_cast<int>(GetHighest());
		return (lowests <= layer && layer <= heights);
	}

	static int GetInt(Layer layer)
	{
		return static_cast<int>(layer);
	}

	static Layer GetLayer(int layer) 
	{
		return static_cast<Layer>(layer);
	}

	static std::vector<Layer> GetAllLayer() 
	{
		std::vector<Layer> result;
		for (int i = GetInt(GetLowest()); i <= GetInt(GetHighest()); i++)
		{
			result.push_back(GetLayer(i));
		}

		return result;
	}

	static std::string GetString(Layer layer) 
	{
		switch (layer)
		{
			case Layer::Background:
				return "Background";
			case Layer::Floor:
				return "Floor";
			case Layer::Wall:
				return "Walls";
			case Layer::Default:
				return "Default";
			case Layer::Player:
				return "Player";
			case Layer::Projectiles:
				return "Projectiles";
			case Layer::Foreground:
				return "Foreground";
			case Layer::EngineLayer:
				return "EngineLayer";
			default:
				return "UNKNOWN";
		}
	}
};
