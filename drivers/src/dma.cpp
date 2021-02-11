#include "dma.hpp"

namespace imxdrivers
{
    dma_t::dma_t(const std::uint32_t &ch) noexcept : dma_ch_(ch)
    {
        dma_mux_t::always_enable(ch, true);
        dma_mux_t::enable(ch, true);
    }
    dma_t::dma_t(const std::uint32_t &ch, const dma_request_source_t &src_request) noexcept : dma_ch_(ch)
    {
        dma_mux_t::set_source(ch, src_request);
        dma_mux_t::enable(ch, true);
    }
    dma_t::~dma_t() = default;

    void dma_t::config(const dma_channel_t &cfg) noexcept
    {
        // Must be done upon sga config
        dma_ch_.clear_done();

        dma_ch_.set_saddr(cfg.tcd_.SADDR);
        dma_ch_.set_daddr(cfg.tcd_.DADDR);
        dma_ch_.set_attr(cfg.tcd_.ATTR);
        dma_ch_.set_soff(cfg.tcd_.SOFF);
        dma_ch_.set_doff(cfg.tcd_.DOFF);
        dma_ch_.set_slast(cfg.tcd_.SLAST);
        dma_ch_.set_nbytes(cfg.tcd_.NBYTES_MLNO);
        dma_ch_.set_citer(cfg.tcd_.CITER);
        dma_ch_.set_biter(cfg.tcd_.BITER);
        dma_ch_.set_dlast(cfg.tcd_.DLAST_SGA);
        dma_ch_.set_csr(cfg.tcd_.CSR);
    }

    
} // namespace imxdrivers