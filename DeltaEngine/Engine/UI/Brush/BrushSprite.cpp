//#include "BrushSprite.hpp"
//
//BrushSprite::BrushSprite(Transform& transform, const std::string& spriteName, SnapToGridBrush* brush)
//{
//	std::string _category = "";
//	_name = spriteName;
//	_inputHandler.Add(InputManager::onMouseButtonDown(
//		MouseButton::Left,
//		[this, &transform, brush](Input& e)
//		{
//			if (!Math::MathUtils::IsVector2WithinRect({e.mouseX, e.mouseY}, transform.position, transform.scale))
//				return;
//
//			brush->SetSprite(_name);
//		},
//		_category));
//};
//
//void BrushSprite::SetSprite(const std::string& name)
//{
//	_name = name;
//}