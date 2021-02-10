#ifndef IMXRT_DRIVERS_DMA_MUX_HPP_
#define IMXRT_DRIVERS_DMA_MUX_HPP_

#include <imxrt1062/hardware.hpp>
#include <imxrt1062/utility.hpp>

#include "reg.hpp"

namespace imxdrivers
{
    using dma_mux_hw_t = DMAMUX_Type *;

    const static dma_mux_hw_t dma_mux_ = DMAMUX;

    class dma_mux_t
    {
    public:
        static void enable(const std::uint32_t &channel, const bool &enable) noexcept
        {
            reg_manipulate_bit(dma_mux_->CHCFG[channel], DMAMUX_CHCFG_ENBL_SHIFT, enable);
        }

        static void always_enable(const std::uint32_t &channel, const bool &enable) noexcept
        {
            reg_manipulate_bit(dma_mux_->CHCFG[channel], DMAMUX_CHCFG_A_ON_SHIFT, enable);
        }

        static void set_source(const std::uint32_t &channel, const dma_request_source_t &source) noexcept
        {
            reg_set(dma_mux_->CHCFG[channel], DMAMUX_CHCFG_SOURCE(source));
        }
    };

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_DMA_MUX_HPP_