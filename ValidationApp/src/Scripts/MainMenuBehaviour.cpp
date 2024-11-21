#include "MainMenuBehaviour.hpp"

void MainMenuBehaviour::OnStart()
{

}

void MainMenuBehaviour::OnUpdate()
{
	if (test >= 150)
	{
		LoadScene("GameScene");
	}

	std::cout << "MainMenu: " << test << std::endl;
	test++;
}
