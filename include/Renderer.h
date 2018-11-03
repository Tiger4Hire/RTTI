#pragma once
#include "ObjectList.h"
#include "RenderPolicy.h"
class Renderer
{
public:
    void RenderAndTranslateThing(Object&, RenderPolicy);
};
