#include "dma_mux.hpp"

namespace imxdrivers
{
    void dma_mux_t::enable(const std::uint32_t &channel, const bool &enable) noexcept
    {
        reg_manipulate_bit(dma_mux_->CHCFG[channel], DMAMUX_CHCFG_ENBL_SHIFT, enable);
    }

    void dma_mux_t::always_enable(const std::uint32_t &channel, const bool &enable) noexcept
    {
        reg_manipulate_bit(dma_mux_->CHCFG[channel], DMAMUX_CHCFG_A_ON_SHIFT, enable);
    }

    void dma_mux_t::set_source(const std::uint32_t &channel, const dma_request_source_t &source) noexcept
    {
        reg_set(dma_mux_->CHCFG[channel], DMAMUX_CHCFG_SOURCE(source));
    }

    void dma_mux_t::enable_clock() noexcept
    {
        const static auto dma_mux_peripherals = DMAMUX_BASE_PTRS;
        const static auto dma_mux_clocks = DMAMUX_CLOCKS;

        dma_mux_clock_spec_t spec(dma_mux_);

        auto clock = clock_t::get_clock(dma_mux_clocks, dma_mux_peripherals, spec);

        imxdrivers::enable_clock(*clock);
    }
} // namespace imxdrivers