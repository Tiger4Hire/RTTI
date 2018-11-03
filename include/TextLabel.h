#pragma once
#include "Object.h"
#include <string>

class TextLabel : public Object
{
    std::string text;
    void DrawMe() final;

public:
    TextLabel(std::string&& ref) : text(std::move(ref)) {}
    void Translate() final;
    ObjectType GetType() final { return ObjectType::TextLabel; }
};