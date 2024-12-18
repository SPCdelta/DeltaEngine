#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include "../Core/Events/EventDispatcher.hpp"
#include "../Core/Math/Point.hpp"
#include "InputEventDispatchers.hpp"
#include "DeltaInputs.hpp"

class InputListener;

class InputManager
{
   public:
	// Singleton
	static InputManager& GetInstance();
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static void deactivateCategory(const std::string& category);
	static void activateCategory(const std::string& category);

	static InputListener* onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);
	static InputListener* keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);
	static InputListener* onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);

	//static void onKeyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent); TODO dit werkt op dit moment niet vanwege executeInputsPressedDown
	static InputListener* keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, const std::string& category = defaultCategory);

	static InputListener* onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category = defaultCategory);
	static InputListener* onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category = defaultCategory);
	static InputListener* onMouseMove(Events::EventCallback<Input&> mouseEvent, const std::string& category = defaultCategory);
	static InputListener* onMouseWheel(Events::EventCallback<Input&> wheelEvent, const std::string& = defaultCategory);


	static Math::Point GetMousePosition();


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(MouseButton button);
	void updateMouseButtonUp(MouseButton button);
	void updateMouseMovement(int x, int y);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

	void Remove(InputType type, const std::string& input, InputState state, const std::string& category, Events::EventCallback<Input&>& regesterd);

	static constexpr const char* defaultCategory = "Default";

   private:
	InputManager();
	static InputManager instance_;

	Input allInputs;

	std::map<InputType, InputEventDispatchers> inputState;

	/*std::map<std::string, Events::EventDispatcher<Input&>> mouseMovement;
	std::map<std::string, Events::EventDispatcher<Input&>> mouseWheelMovement;*/
};



class InputListener {
public:
    InputListener(InputType type, const std::string& input, InputState state, const std::string& category, Events::EventCallback<Input&> regesterd)
        : _type{ type }, _input{ input }, _state{ state }, _category{ category }, _regesterd{ regesterd } {}

    ~InputListener() {
        InputManager::GetInstance().Remove(_type, _input, _state, _category, _regesterd);
    }

    //InputListener(const InputListener&) = delete;
    //InputListener& operator=(const InputListener&) = delete;

    //InputListener(InputListener&& other) noexcept
    //    : _type{ other._type },
    //    _state{ other._state },
    //    _input{ std::move(other._input) },
    //    _category{ std::move(other._category) },
    //    _regesterd{ other._regesterd }
    //{}

    //InputListener& operator=(InputListener&& other) noexcept {
    //    if (this != &other) {

    //        _type = other._type;
    //        _state = other._state;
    //        _input = std::move(other._input);
    //        _category = std::move(other._category);
    //        _regesterd = other._regesterd;
    //    }
    //    return *this;
    //}

private:
    InputType _type;
    InputState _state;
    std::string _input;
    std::string _category;
    Events::EventCallback<Input&> _regesterd;
};

class InputHandler
{
public:
    InputHandler() {}

    ~InputHandler()
    {
        for (InputListener* il : _inputListeners)
        {
            delete il;
        }
        _inputListeners.clear();
    }

    void Add(InputListener* il)
    {
        _inputListeners.push_back(il);
    }

private:
    std::vector<InputListener*> _inputListeners{};
};