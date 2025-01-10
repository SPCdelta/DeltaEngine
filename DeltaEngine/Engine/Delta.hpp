#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Application.hpp"
#include "GameObject.hpp"
#include "BehaviourScript.hpp"
#include "Scene/Scene.hpp"

// Files
#include "Core/Files/FileManager.hpp"
#include "Core/Files/DTO/TransformDTO.hpp"
#include "Core/Files/DTO/SpriteDTO.hpp"

// Audio
#include "Audio/AudioManager.hpp"

// Time
#include "Core/Time.hpp"

// Math
#include "Core/Math/Math.hpp"
#include "Core/Math/MathUtils.hpp"
#include "Core/Math/Random.hpp"

// String
#include "Core/Strings/StringUtils.hpp"

// Rendering
#include "Rendering/Layer.hpp"
#include "Rendering/SpriteMap.hpp"

// Particles
#include "Rendering/Particles/ParticleEmitter.hpp"

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
