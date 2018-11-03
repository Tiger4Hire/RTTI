#pragma once

/*************************************************************************
 * Object is now just a "concept".
 *
 * Added "DoNothing" so we can compare overhead of calls
 *************************************************************************/

class Object
{
public:
    virtual void DoNothing() const = 0;
};