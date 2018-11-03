#pragma once
#include "Object.h"
#include <string>

class TextLabel : public RenderedObject<RenderPolicy::TranslateAndRender>
{
    std::string text;
    void DrawMe() final;

public:
    TextLabel(std::string&& ref) : text(std::move(ref)) {}
    void Translate() final;
};