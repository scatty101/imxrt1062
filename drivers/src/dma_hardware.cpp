#include "dma_hardware.hpp"

namespace imxdrivers
{

    dma_hardware_t::dma_hardware_t(const std::uint32_t &channel) noexcept : channel_(channel)
    {
        dma_mux_t::enable_clock();
        enable_clock();
    }

    dma_hardware_t::~dma_hardware_t() = default;

    void dma_hardware_t::enable_clock() noexcept
    {
        const static auto dma_peripherals = DMA_BASE_PTRS;
        const static auto dma_clocks = EDMA_CLOCKS;

        dma_clock_spec_t spec(dma_);

        auto clock = clock_t::get_clock(dma_clocks, dma_peripherals, spec);

        imxdrivers::enable_clock(*clock);
    }
} // namespace imxdrivers