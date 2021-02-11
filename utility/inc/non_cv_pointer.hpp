#ifndef IMXRT_DRIVERS_NON_CV_POINTER_HPP_
#define IMXRT_DRIVERS_NON_CV_POINTER_HPP_

#include <cstdint>
#include <type_traits>

namespace imxutility
{
    template <typename T, typename non_cv_t = std::remove_cv_t<T>>
    constexpr T *non_cv_pointer(T *ptr)
    {
        return const_cast<non_cv_t *>(ptr);
    }

    template <typename new_ptr_t, typename old_ptr_t>
    constexpr new_ptr_t r_non_cv_pointer(old_ptr_t *ptr)
    {
        auto non_cv_ptr = non_cv_pointer(ptr);
        return reinterpret_cast<new_ptr_t>(non_cv_ptr);
    }

} // namespace imxutility

#endif // IMXRT_DRIVERS_NON_CV_POINTER_HPP_