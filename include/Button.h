#pragma once
#include "Object.h"

class Button : public Object
{
    void DrawMe() final;
    virtual RenderPolicy GetRenderPolicy() final
    {
        return RenderPolicy::TranslateAndRender;
    }
};