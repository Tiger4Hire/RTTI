#include "Object.h"

// RED FLAG : GetPolicy is a member function that uses NO members.
// This change is taking to us towards something, but is obviously not complete

RenderPolicy Object::GetRenderPolicy(ObjectType type)
{
    switch (type)
    {
        case ObjectType::TextLabel:
            return RenderPolicy::TranslateAndRender;
        default:
            return RenderPolicy::Render;
    }
}
