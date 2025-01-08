#pragma once

#include "Engine/Delta.hpp"

class FileScene : public Scene
{
public:
	FileScene(const std::string& name);

	void OnStart() override;
};
