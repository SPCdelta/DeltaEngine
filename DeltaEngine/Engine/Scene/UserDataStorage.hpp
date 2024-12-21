#pragma once
#include "../Core/Files/Json.hpp"


class StoreUserData
{
public:
	void Store(const std::string& data);
	void Store(const Json::json& jsonObject);
	Json::json& Retrive();
	void DeleteData();
	void DeleteData(const std::string& data);

private:
	Json::json _userData;

	static constexpr const char DATA_NAME[] = "scene_data";
};
