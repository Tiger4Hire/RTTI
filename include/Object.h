#pragma once
#include "RenderPolicy.h"
/*************************************************************************
 * This is a pretty stupid use of a pure-interface. Object is so generic
 * that it is meaningless, and DrawMe is so generic, it may as well be called
 * "DoStuff". However, this type of coding is depressingly common, and this
 * example is to show how to re-engineer bad code. This fits my need.
 *************************************************************************/
class Object
{
public:
    // public interface designed to be polymporphically owned implies rule of 5
    // defaults
    Object() = default;
    virtual ~Object() = default;
    Object(const Object&) = default;
    Object& operator=(const Object&) = default;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;
    // useful stuff
    virtual void DrawMe() = 0;
    virtual void Translate() {}
    virtual RenderPolicy GetRenderPolicy() { return RenderPolicy::None; }
};

template <RenderPolicy policy>
class RenderedObject : public Object
{
public:
    virtual RenderPolicy GetRenderPolicy() final { return policy; }
};