#include "Layer.hpp"

Layer LayerHelper::GetLowest()
{
	return Layer::Background;
}

Layer LayerHelper::GetHighest()
{
	return Layer::Foreground;
}

bool LayerHelper::InLayers(int layer)
{
	int lowests = static_cast<int>(GetLowest());
	int heights = static_cast<int>(GetHighest());
	return (lowests <= layer && layer <= heights);
}

int LayerHelper::GetInt(Layer layer)
{
	return static_cast<int>(layer);
}

Layer LayerHelper::GetLayer(int layer)
{
	return static_cast<Layer>(layer);
}

std::vector<Layer> LayerHelper::GetAllLayer()
{
	std::vector<Layer> result;
	for (int i = GetInt(GetLowest()); i <= GetInt(GetHighest()); i++)
		result.push_back(GetLayer(i));
	return result;
}

std::string LayerHelper::GetString(Layer layer)
{
	switch (layer)
	{
		case Layer::Background:
			return "Background";
		case Layer::Button:
			return "Button";
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