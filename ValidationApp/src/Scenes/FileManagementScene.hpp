#pragma once

#include <fstream>

#include "Engine/Delta.hpp"
#include "json/json.hpp"

using json = nlohmann::json;

class FileManagementScene : public Scene
{
	public:
		FileManagementScene(const std::string& sceneName) : Scene(sceneName)
		{
			// File loading
			std::ifstream inputFile("Assets\\Files\\example.json");
			if (inputFile.is_open())
			{
				json load = json::parse(inputFile); // Access with load["hello"]
				inputFile.close();
			}

			// File saving
			json save;
			save["testing"] = "meow";
			
			// Save to a new file
            std::ofstream newFile("Assets\\Files\\new_file.json");
            if (newFile.is_open())
			{
                newFile << save.dump(4); // 4 spaces indentation
                newFile.close();
            }

            // Save to an existing file (append or overwrite)
            std::ofstream existingFile("Assets\\Files\\example.json", std::ios::out | std::ios::trunc);
            if (existingFile.is_open()) 
			{
                existingFile << save.dump(4); 
                existingFile.close();
            }
		}
};