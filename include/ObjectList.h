#pragma once
#include "Object.h"
#include <memory>
#include <list>

/**************************************************************************
 * While Object interface may be bad, this is where the real damage is done.
 * We "cast" away all knowledge of what the object is, just to make iteration
 * through the objects a "tiny-bit" easy. A very poor swap. Generally, you
 * should never "own" polymorphically. If this list was "non-owning" it would
 * fine.
 **************************************************************************/

using ObjectList =
    std::list<std::unique_ptr<Object>>;  // in other words - a bag of crap
