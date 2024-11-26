#pragma once

#include <fstream>

#include "json/json.hpp"
#include "IFileHandler.hpp"

using json = nlohmann::json;

class JSONFileHandler : public IFileHandler
{
	public:
	// 'Assets\\Files\\' needs to be in the path with the file name at the end
		json LoadFile(const std::string& path) override
		{
			json data;
			std::ifstream file(path);
			if (file.is_open())
			{
				file >> data;  // Access with data["something"];
				file.close();
			}

			return data;
		}

		// 'Assets\\Files\\' needs to be in the path with the file name at the end
		void SaveFile(const std::string& path, const json& data) override
		{
			std::ofstream file(path, std::ios::out | std::ios::trunc);
			if (file.is_open())
			{
				file << data.dump(4);
				file.close();
			}
		}
};