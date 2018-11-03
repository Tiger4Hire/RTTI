#pragma once
#include "Object.h"

class Button : public RenderedObject<RenderPolicy::TranslateAndRender>
{
    void DrawMe() final;
};