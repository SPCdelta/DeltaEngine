#pragma once

#include <iostream>
#include <vector>

#include "Application.hpp"
#include "GameObject.hpp"
#include "BehaviourScript.hpp"
#include "Scene/Scene.hpp"

// Components
#include "Core/Despawner.hpp"

// Files
#include "Core/Files/FileManager.hpp"
#include "Core/Files/DTO/TransformDTO.hpp"

//Audio
#include "Audio/AudioManager.hpp"

// Time
#include "Core/Time.hpp"

// Math
#include "Core/Math/Math.hpp"
#include "Core/Math/MathUtils.hpp"

// String
#include "Core/Strings/StringUtils.hpp"

// Rendering
#include "Rendering/Layer.hpp"
#include "Rendering/SpriteMap.hpp"

// Input
#include "Input/DeltaInputs.hpp"
#include "Input/InputHandler.hpp"

// Physics
using namespace Physics;
#include "Physics/BoxCollider.hpp"
#include "Physics/CircleCollider.hpp"
#include "Physics/Rigidbody.hpp"

// UI
#include "UI/Text.hpp"
#include "UI/Image.hpp"
#include "UI/Button.hpp"
#include "UI/Brush/SnapToGridBrush.hpp"

// AI
#include "Core/AI/AIBehaviour.hpp"
#include "Core/AI/AStarStrategy.hpp"
