#include "Renderer.h"

void Renderer::RenderAndTranslateThing(Object& thing, RenderPolicy policy)
{
    switch (policy)
    {
        case RenderPolicy::TranslateAndRender:
            thing.Translate();
            [[fallthrough]];  // disable warning that there is no break
        default:
            thing.DrawMe();
    }
}