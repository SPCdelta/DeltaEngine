#pragma once

#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include "../Core/Events/Event.hpp"
#include "../Core/Events/EventDispatcher.hpp"
#include "DeltaInputs.hpp"

class InputListener;

//namespace Events
//{
//
//	class InputEventDispatcher
//	{
//	public:
//		void Register(Events::EventCallback<Input> callback)
//		{
//			m_Callbacks = callback;
//		}
//
//		void Unregister(Events::EventCallback<Input> callback)
//		{
//			auto it = std::find_if(m_Callbacks.begin(), m_Callbacks.end(),
//				[&callback](const Events::EventCallback<T>& cb)
//				{
//					return callback.target<void(Input&)>() == cb.target<void(Input&)>();
//				});
//
//			if (it != m_Callbacks.end()) {
//				m_Callbacks.erase(it);
//			}
//		}
//
//		void Dispatch(T& event)
//		{
//			for (size_t i = 0; i < m_Callbacks.size(); ++i)
//			{
//				m_Callbacks[i](event);
//			}
//		}
//
//	private:
//		Events::EventCallback<Input> m_Callbacks{};
//	};
//}

class InputEventDispatchers
{
   public:
	void Add(InputListener* input);
	void Remove(InputListener* input);

	bool Find(InputState state, const std::string& input);
	void DispatchActive(InputState state, const std::string& input, Input inputEvent);


	void ExecuteInputsPressedDown(Input allInputs, std::vector<std::string>& strInputs, const std::string& strPressedDown);
	void ExecuteInputsPressed(Input allInputs, std::vector<std::string>& strInputs);
   

private:
	std::map<InputState, std::map<std::string, Events::EventDispatcher<Input&>>> inputBindings;
	
};


