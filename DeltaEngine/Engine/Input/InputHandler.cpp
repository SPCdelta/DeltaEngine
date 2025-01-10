#include "InputHandler.hpp"

InputHandler::~InputHandler()
{
    for (InputListener* il : _inputListeners)
    {
        if (il->GetType() == -572662307)
        {
            // TODO: JeroenYurian
			continue;
        }
        delete il;
    }
    _inputListeners.clear();
}

void InputHandler::Add(InputListener* il)
{
    _inputListeners.push_back(il);
}

InputType InputListener::GetType() const {
    return _type;
}

InputState InputListener::GetState() const {
    return _state;
}

const std::string& InputListener::GetInput() const {
    return _input;
}

const std::string& InputListener::GetCategory() const {
    return _category;
}

const Events::EventCallback<Input&>& InputListener::GetRegistered() const {
    return _registered;
}
