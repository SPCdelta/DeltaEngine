#pragma once

#include <string>
#include <functional>

#include "../../GameObject.hpp"
#include "../../Rendering/Sprite.hpp"

class Brush
{
public:
	Brush
	(
		const std::string& name, Key shortcut, GameObject* object, 
		std::function<void()> onActivate, std::function<void()> onRelease, std::function<void(Brush*)> onRepeat
	)
		: _name{ name }, _shortcut{ shortcut }, _categoryName{ "brush_" + name }, 
		_object{ object },
		_onActivate{ onActivate }, _onRelease{ onRelease }, _onRepeat{ onRepeat }
	{
		_sprite = object->AddComponent<Sprite>("default_texture");
		_sprite->SetLayer(Layer::EngineLayer);
		_sprite->SetVisible(false);

		_inputHandler.Add(InputManager::onMouseButtonDown(MouseButton::Left, 
			[this](Input& e)
			{
				if (_isActive)
				{
					Activate();
				}
			},
			_categoryName
		));

		_inputHandler.Add(InputManager::onMouseButtonUp(MouseButton::Left,
			[this](Input& e) 
			{ 
				if (_isActive)
				{
					Release();
				}
			},
			_categoryName
		));

		// MoveObject Along
		_inputHandler.Add(InputManager::onMouseMove(
			[this](Input& e)
			{
				_object->transformRef.position.Set(_object->GetCamera()->ToWorldGrid({e.mouseX, e.mouseY}));

				if (_beingUsed)
				{
					Repeat();
				}
					
			}, _categoryName
		));
	}

	Key Shortcut() const { return _shortcut; }

	bool IsActive() const { return _isActive; }
	bool BeingUsed() const { return _beingUsed; }

	void Enable()
	{
		InputManager::activateCategory(_categoryName);
		_isActive = true;
		_sprite->SetVisible(true);
	}

	void Disable()
	{
		InputManager::deactivateCategory(_categoryName);
		_isActive = false;
		_sprite->SetVisible(false);
	}

	void Toggle()
	{
		if (_isActive)
		{
			Disable();
		}
		else
		{
			Enable();
		}
	}

	void NotifyTransform()
	{
		if (!_beingUsed)
			return;
	
		_object->transformRef.position.Set(_object->GetCamera()->ToWorldGrid(InputManager::GetMousePosition()));
		OnRepeat();
		_onRepeat(this);
	}

	const std::string& GetName() const { return _name; }
	Sprite* GetSprite() const { return _sprite; }
	const Vector2& GetPosition() const { return _object->transformRef.position; }

protected:
	InputHandler _inputHandler;
	GameObject* _object;
	Sprite* _sprite = nullptr;


	void Activate()
	{
		_beingUsed = true;
		OnActivate();
		_onActivate();
	}

	void Release()
	{
		_beingUsed = false;
		OnRelease();
		_onRelease();
	}

	void Repeat()
	{
		OnRepeat();
		_onRepeat(this);
	}
	virtual void OnActivate() {}
	virtual void OnRelease() {}
	virtual void OnRepeat() {}

private:
	std::string _name;
	std::string _categoryName;
	Key _shortcut;

	bool _isActive = false;
	bool _beingUsed = false;

	std::function<void()> _onActivate;
	std::function<void()> _onRelease;
	std::function<void(Brush*)> _onRepeat;
};