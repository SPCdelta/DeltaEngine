#pragma once

#include <fstream>

#include "Json.hpp"
#include "IFileHandler.hpp"

class JSONFileHandler : public IFileHandler
{
	public:
		static const int TAB_SPACE = 4;

		// 'Assets\\Files\\' needs to be in the path with the file name at the end
		Json::json LoadFile(const std::string& path) override
		{
			Json::json data;
			std::ifstream file(path);
			if (file.is_open())
			{
				// Check if the file is empty
                file.seekg(0, std::ios::end); 
                std::streampos fileSize = file.tellg();
                if (fileSize > 0)
                {
                    file.seekg(0, std::ios::beg); 
                    try
                    {
                        file >> data; // Parse JSON
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << "Error parsing JSON file: " << e.what() << std::endl;
                        data = Json::json::object(); // Return empty JSON object on error
                    }
                }

                file.close();
            }
            else
            {
                std::cerr << "Error opening file: " << path << std::endl;
            }

            return data;
		}

		// 'Assets\\Files\\' needs to be in the path with the file name at the end
		void SaveFile(const std::string& path, const Json::json& data) override
		{
			std::ofstream file(path, std::ios::out | std::ios::trunc);
			if (file.is_open())
			{
				file << data.dump(TAB_SPACE);
				file.close();
			}
		}
};