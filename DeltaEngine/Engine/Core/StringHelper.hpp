#pragma once

#include <iostream>
#include <vector>


namespace String{

	inline std::vector<std::string> split(const std::string& str, char splitValue){
		std::vector<std::string> parts;
		size_t pos = 0;
		size_t found;

		while ((found = str.find('_', pos)) != std::string::npos) {
			parts.push_back(str.substr(pos, found - pos));
			pos = found + 1;
		}
		parts.push_back(str.substr(pos));

		return parts;
	}

}