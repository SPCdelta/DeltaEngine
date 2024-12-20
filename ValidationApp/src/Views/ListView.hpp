#pragma once

#include "IView.hpp"
#include "ListViewItem.hpp"

class ListView : public IView
{
public:
	ListView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, Uint8 numOfRows, const ListViewItem& item);
	const Math::Vector2& GetSize() const override;
private:
	void InitItems(const ListViewItem& item);
	Uint8 _numOfRows;
	std::vector<ListViewItem> _children;
};

