#include "InputHandler.hpp"

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{
    for (InputListener* il : _inputListeners)
    {
        delete il;
    }
    _inputListeners.clear();
}

void InputHandler::Add(InputListener* il)
{
    _inputListeners.push_back(il);
}

InputListener::InputListener(InputType type, const std::string& input, InputState state, const std::string& category, Events::EventCallback<Input&> registered)
	: _type{type},
	  _input{input},
	  _state{state},
	  _category{category},
	  _registered{registered}
{

}

InputListener::~InputListener()
{
	InputManager::GetInstance().Remove(this);
}

InputType InputListener::GetType() const 
{
    return _type;
}

InputState InputListener::GetState() const 
{
    return _state;
}

const std::string& InputListener::GetInput() const 
{
    return _input;
}

const std::string& InputListener::GetCategory() const 
{
    return _category;
}

const Events::EventCallback<Input&>& InputListener::GetRegistered() const 
{
    return _registered;
}
