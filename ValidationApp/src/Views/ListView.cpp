#include "ListView.hpp"

ListView::ListView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, Uint8 numOfRows, const ListViewItem& item)
	: IView(scene, fontName, startPos, {}), _numOfRows{numOfRows}
{
	InitItems(item);
}

const Math::Vector2& ListView::GetSize() const
{
	return _scale;
}

void ListView::InitItems(const ListViewItem& item)
{
	auto pos = _pos;
	for (Uint8 i = 0; i < _numOfRows; ++i)
	{
		auto child = ListViewItem{item};
		child.Show();
		child.SetPosition(pos);
		_children.emplace_back(child);
		pos.AddY(100); // TODO: y margin
	}
}
