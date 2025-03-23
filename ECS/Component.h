#ifndef IG20250323182427
#define IG20250323182427

#include "Id.h"

namespace snx
{
    using ComponentTypeId = Id;

    struct IComponent
    {
        virtual ~IComponent() = default;

    protected:
        static inline ComponentTypeId componentTypeId_{0};
    };

    class Component : public IComponent
    {
    public:
        static inline ComponentTypeId getId()
        {
            //* Initialized only once per templated type because it is static
            static ComponentTypeId id{++componentTypeId_};

            return id;
        }
    };
}

#endif
