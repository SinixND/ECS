#ifndef IG20250323182427
#define IG20250323182427

#include "Id.h"

namespace snx
{
    struct CTypeCounter
    {
        static inline Id counter{0};
    };

    template <typename T>
    class Component : public CTypeCounter
    {
    public:
        static inline Id typeId()
        {
            static Id id{++counter};

            return id;
        }
    };
}

#endif
