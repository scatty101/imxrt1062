#ifndef IMXRT_DRIVERS_DMA_HPP_
#define IMXRT_DRIVERS_DMA_HPP_

#include <cstdint>

#include "dma_hardware.hpp"

namespace imxdrivers
{
    class dma_channel_t
    {
        const std::uint32_t ch_;

    public:
        dma_channel_t(const std::uint32_t ch) : ch_(ch)
        {
            dma_hardware_t<ch_>::request_clear();
        }
    };
} // namespace imxdrivers

#endif // IMXRT_DRIVERS_DMA_HPP_