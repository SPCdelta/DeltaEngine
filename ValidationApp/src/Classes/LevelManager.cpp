#include "LevelManager.hpp"

void LevelManager::GetLevels(std::vector<std::string>& levels, bool save = true)
{
	EnsureSettingsFile();

	// Get Settings
	FileManager fileManager{};
	Json::json file = fileManager.Load(LevelSettingsPath, "json");
	std::vector<std::string> existingFiles = FileManager::filesInDirectory(LevelsPath);

	// Levels
	size_t buttonAmount{0};
	for (size_t i = 0; i < file["levels"].size(); i++)
	{
		std::string levelName = file["levels"][i];

		// Check if Valid
		auto it = std::find(existingFiles.begin(), existingFiles.end(), levelName);
		if (it != existingFiles.end()) // Exists
			existingFiles.erase(it);
		else
			continue;

		levels.push_back(levelName);
		buttonAmount++;
	}

	for (std::string& file : existingFiles)
	{
		levels.push_back(file);
		buttonAmount++;
	}

	if (save)
		LevelManager::SaveLevelSettings(levels);
}

void LevelManager::SaveLevelSettings(std::vector<std::string>& files)
{
	FileManager fileManager{};
	Json::json levelsJson;

	for (size_t i = 0; i < files.size(); ++i)
		levelsJson["levels"][i] = files[i];

	fileManager.Save(LevelSettingsPath, "json", levelsJson);
}

std::string LevelManager::FormatDisplayName(const std::string& levelName)
{
	std::string uhm = std::filesystem::path(levelName).stem().string();
	if (uhm.length() > 16)
		return uhm.substr(0, 13) + "...";
	return uhm;
}

void LevelManager::EnsureSettingsFile()
{
	if (!FileManager::FileExists(LevelSettingsPath))
	{
		std::vector<std::string> directoryFiles = FileManager::filesInDirectory(LevelsPath);
		LevelManager::SaveLevelSettings(directoryFiles);
	}
}