#ifndef IMXRT_DRIVERS_DMA_MUX_HPP_
#define IMXRT_DRIVERS_DMA_MUX_HPP_

#include <imxrt1062/hardware.hpp>
#include <imxrt1062/utility.hpp>

#include "reg.hpp"
#include "clocks.hpp"

namespace imxdrivers
{
    using dma_mux_hw_t = DMAMUX_Type *;

    const static dma_mux_hw_t dma_mux_ = DMAMUX;

    class dma_mux_clock_spec_t : public default_spec_t<dma_mux_hw_t>
    {
    public:
        using default_spec_t<dma_mux_hw_t>::default_spec_t;
    };

    class dma_mux_t
    {
    public:
        static void enable(const std::uint32_t &channel, const bool &enable) noexcept;
        static void always_enable(const std::uint32_t &channel, const bool &enable) noexcept;
        static void set_source(const std::uint32_t &channel, const dma_request_source_t &source) noexcept;
        static void enable_clock() noexcept;
    };

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_DMA_MUX_HPP_