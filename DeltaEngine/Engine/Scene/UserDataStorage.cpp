#include "UserDataStorage.hpp"

void StoreUserData::Store(const std::string& data)
{
	DeleteData(DATA_NAME);
	_userData[DATA_NAME] = data;
}

void StoreUserData::Store(const Json::json& jsonObject)
{
	DeleteData(DATA_NAME);
	_userData[DATA_NAME] = jsonObject;
}

Json::json& StoreUserData::Retrieve()
{
	return _userData[DATA_NAME];
}

void StoreUserData::DeleteData()
{
	DeleteData(DATA_NAME);
}

void StoreUserData::DeleteData(const std::string& data)
{
	if (_userData.contains(DATA_NAME))
		_userData.erase(DATA_NAME);
}
