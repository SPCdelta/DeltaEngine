#pragma once

#include <Engine/Delta.hpp>

class LevelManager
{
public:
	static constexpr auto LevelSettingsPath = "Assets\\Settings\\levels.json";
	static constexpr auto LevelsPath = "Assets\\Level";

	static void GetLevels(std::vector<std::string>& levels, bool save = true);
	static void SaveLevelSettings(std::vector<std::string>& files);

	static std::string FormatDisplayName(const std::string& levelName);

private:
	static void EnsureSettingsFile();
};