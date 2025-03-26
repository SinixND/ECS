#ifndef SIGNATURE_H_20231220225930
#define SIGNATURE_H_20231220225930

#include <bitset>
#include <cstddef>

namespace snx
{
    size_t constexpr MAX_COMPONENTS = 40;
    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif
