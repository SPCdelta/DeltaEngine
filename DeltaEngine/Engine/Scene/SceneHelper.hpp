#pragma once

#include "../Application.hpp"
#include "Scene.hpp"

class SceneHelper
{
public:
	template <typename T>
	static T* GetSceneData(Scene* scene)
	{
		return reinterpret_cast<T*>(scene->_application->GetUserData());
	}

	template <typename T>
	static void SetSceneData(Scene* scene, T* data)
	{
		scene->_application->DeleteUserData(); //TODO hier zit een memory leak
		scene->_application->SetUserData(reinterpret_cast<void*>(data));
	}
};