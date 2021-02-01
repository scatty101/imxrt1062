#if !defined IMXRT1062_UTILITY_ARRAY_SIZE_H_
#define IMXRT1062_UTILITY_ARRAY_SIZE_H_

#include <cstdint>

namespace utility
{
    template <typename T, std::size_t N>
    std::size_t array_size(T (&)[N])
    {
        return N;
    }
} // namespace utility

#endif // IMXRT1062_UTILITY_ARRAY_SIZE_H_
