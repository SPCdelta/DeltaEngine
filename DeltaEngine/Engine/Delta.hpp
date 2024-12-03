#pragma once

#include <iostream>

#include "GameObject.hpp"
#include "BehaviourScript.hpp"
#include "Scene/Scene.hpp"

#include "Core/Files/FileManager.hpp"

//Audio
#include "Audio/AudioFacade.hpp"

// Time
#include "Core/Time.hpp"

// Math
#include "Core/Math/MathUtils.hpp"

// Rendering
#include "Rendering/Layer.hpp"
#include "Rendering/SpriteMap.hpp"

// Input
#include "Input/DeltaInputs.hpp"

// Physics
using namespace Physics;
#include "Physics/BoxCollider.hpp"
#include "Physics/CircleCollider.hpp"
#include "Physics/Rigidbody.hpp"

// UI
#include "UI/Text.hpp"
#include "UI/Image.hpp"
#include "UI/Button.hpp"
