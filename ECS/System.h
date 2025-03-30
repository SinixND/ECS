#ifndef IG20250326001359
#define IG20250326001359

#include "Id.h"
#include <unordered_set>

namespace snx
{
    struct System
    {
        std::unordered_set<Id> entities;
    };
}

#endif
