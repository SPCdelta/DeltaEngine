#pragma once

#include <fstream>

#include "json/json.hpp"
#include "IFileHandler.hpp"

using json = nlohmann::json;

class JSONFileHandler : public IFileHandler
{
	public:
		json LoadFile(const std::string& path) override // TODO "Assets\\Files\\example.json" to test
		{
			json data;
			std::ifstream file(path);
			if (file.is_open())
			{
				file >> data;  // Access with data["hello"]
				file.close();
			}

			return data;
		}

		void SaveFile(const std::string& path, const json& data) override // TODO "Assets\\Files\\new_file.json" to test
		{
			/*json save;
			save["testing"] = "meow";*/ // TODO save things

			// Save to a new file
			std::ofstream file(path);
			if (file.is_open())
			{
				file << data.dump(4);
				file.close();
			}

			// TODO commented code
			// Save to an existing file (append or overwrite)
			/*std::ofstream existingFile("Assets\\Files\\example.json", std::ios::out | std::ios::trunc);
			if (existingFile.is_open())
			{
				existingFile << save.dump(4);
				existingFile.close();
			}*/
		}
};