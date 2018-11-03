#pragma once
#include "Button.h"
#include "TextLabel.h"
#include <memory>
#include <list>
#include <vector>

/**************************************************************************
 * While Object interface may be bad, this is where the real damage is done.
 * We "cast" away all knowledge of what the object is, just to make iteration
 * through the objects a "tiny-bit" easy. A very poor swap. Generally, you
 * should never "own" polymorphically. If this list was "non-owning" it would
 * fine.
 **************************************************************************/

class ObjectList
{
    enum ObjectType
    {
        ButtonType,
        TextLabelType
    };
    std::vector<TextLabel> labels;
    std::vector<Button> buttons;
    std::vector<ObjectType> typeOrder;

public:
    void emplace_back(Button&&);
    void emplace_back(TextLabel&&);
    void erase(int);
    template <class Fn>
    void visit(Fn&& fn);
};
template <class Fn>
void ObjectList::visit(Fn&& fn)
{
    auto pButton = std::begin(buttons);
    auto pLabel = std::begin(labels);
    for (auto type : typeOrder)
    {
        switch (type)
        {
            case ButtonType:
                fn(*pButton++);
                break;
            case TextLabelType:
                fn(*pLabel++);
                break;
        }
    }
}
