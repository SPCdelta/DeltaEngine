#pragma once

#include "InputManager.hpp"

class InputListener 
{
public:
    InputListener(InputType type, const std::string& input, InputState state, const std::string& category, Events::EventCallback<Input&> registered);
    ~InputListener();

    InputType GetType() const;
    InputState GetState() const;

    const std::string& GetInput() const;
    const std::string& GetCategory() const;

    const Events::EventCallback<Input&>& GetRegistered() const;

private:
    InputType _type;
    InputState _state;

    std::string _input;
    std::string _category;

    Events::EventCallback<Input&> _registered;
};

class InputHandler
{
public:
	InputHandler();
    ~InputHandler();

    void Add(InputListener* il);

private:
    std::vector<InputListener*> _inputListeners{};
};