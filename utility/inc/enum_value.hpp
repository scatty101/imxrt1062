#if !defined IMXRT1062_UTILITY_ENUM_VALUE_H
#define IMXRT1062_UTILITY_ENUM_VALUE_H

#include <cstdint>
#include <type_traits>

namespace utility
{
    template <typename enum_t>
    constexpr auto enum_value(enum_t enum_val)
    {
        static_assert(std::is_enum_v<enum_t>, "error: is not enum value");
        return (static_cast<std::underlying_type_t<enum_t>>(enum_val));
    }

} // namespace utility

#endif // IMXRT1062_UTILITY_ENUM_VALUE_H
