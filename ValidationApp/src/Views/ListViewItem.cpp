#include "ListViewItem.hpp"

ListViewItem::ListViewItem(Scene& scene, const std::string& bgSpriteName, const std::string& spriteName, const std::string& fontName,
    const std::string& text, const Math::Vector2& scale) : IView(scene, "", {}, scale), _spriteName{spriteName}, 
    _text{text}, _bgSpriteName{bgSpriteName}
{

}

void ListViewItem::Show()
{
    _item = _scene.Instantiate({ _pos, 0.0f, _scale });
    if (!_text.empty())
    {
        auto font = _fontName.empty() ? DEFAULT_FONT : _fontName;
        _item->AddComponent<Ui::Text>(_text, font, 10, DEFAULT_COLOR); // TODO: change font size
    }
    if (!_spriteName.empty())
    {
        _item->AddComponent<Ui::Image>(_spriteName);
    }
}

const Math::Vector2& ListViewItem::GetSize() const
{
    return _scale;
}

void ListViewItem::SetPosition(const Math::Vector2& pos)
{
    _item->transform->position = pos;
}
