#include "Renderer.h"
#include "RenderPolicy.h"

void Renderer::RenderAndTranslateThing(Object& thing)
{
    switch (thing.GetRenderPolicy(thing.GetType()))
    {
        case RenderPolicy::TranslateAndRender:
            thing.Translate();
            [[fallthrough]];  // disable warning that there is no break
        default:
            thing.DrawMe();
    }
}