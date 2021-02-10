#ifndef IMXRT_DMA_HARDWARE_HPP_
#define IMXRT_DMA_HARDWARE_HPP_

#include "dma_mux.hpp"

namespace imxdrivers
{
    using dma_hw_t = DMA_Type *;
    static const dma_hw_t dma_ = DMA0;

    class dma_hardware_t
    {
        const std::uint32_t channel_;

    public:
        dma_hardware_t(const dma_hardware_t &) = delete;
        dma_hardware_t &operator=(const dma_hardware_t &) = delete;

        dma_hardware_t(const std::uint32_t &channel);
    };

} // namespace imxdrivers

#endif // IMXRT_DMA_HARDWARE_HPP_