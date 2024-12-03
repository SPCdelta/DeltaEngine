#include "InputTest.hpp"
#pragma once

#include <iostream>
#include "Engine/Delta.hpp"

void InputTest::OnStart()
{

	std::cout << "OnStart" << std::endl;

	onKeyPressed(
		KEY_ESCAPE, [this](Input& key) { LoadScene("MainMenuScene"); });

	onKeyPressed(
		KEY_Z, [](Input& key) { std::cout << "Z test" << std::endl; }, "test");

	onKeyPressed(
		KEY_U, [](Input& key) { std::cout << "U test" << std::endl; }, "test");

	onKeyPressed(
		KEY_P, [](Input& key) { std::cout << "P test" << std::endl; }, "test");

	InputManager::deactivateCategory("test");
	InputManager::activateCategory("test");
	keyPressed({KEY_I, KEY_W},
			   [](Input& key)
			   {
				   std::cout << "Gaat naar boven: ";
				   std::for_each(key.keys.begin(), key.keys.end(),
								 [](Key k)
								 { std::cout << InputsEnum::toStr(k); });
				   std::cout << '\n';
			   });

	keyPressed(KEY_A,
			   [](Input& key)
			   {
				   std::cout << "Gaat naar boven: ";
				   std::for_each(key.keys.begin(), key.keys.end(),
								 [](Key k)
								 { std::cout << InputsEnum::toStr(k); });
			   });

	onKeyReleased(KEY_SPACE,
				  [](Input& key)
				  {
					  std::for_each(key.keys.begin(), key.keys.end(),
									[](Key k)
									{ std::cout << InputsEnum::toStr(k); });
					  std::cout << '\n';
				  });

	onMouseButtonDown(MouseButton::Left,
					  [](Input& button)
					  {
						  std::cout << "left: ";
						  std::for_each(button.buttons.begin(),
										button.buttons.end(),
										[](MouseButton k)
										{
											int d = static_cast<int>(k);
											std::cout << d;
										});
						  std::cout << std::endl;
					  });
	//unregesterInputs();

	onMouseButtonUp(MouseButton::Right,
					[](Input& button)
					{
						std::cout << "right: ";
						std::for_each(button.buttons.begin(),
									  button.buttons.end(),
									  [](MouseButton k)
									  {
										  int d = static_cast<int>(k);
										  std::cout << d;
									  });
						std::cout << std::endl;
					});

	/*InputManager::GetInstance().onMouseMove(
			[](Input& mouse) {
				std::cout << mouse.mouseX << " - " << mouse.mouseY << std::endl;
			});*/

	onMouseWheel(
		[](Input& mouse) {
			std::cout << mouse.mouseX << " - " << mouse.wheelVertically
					  << " : \n";
		});
}

