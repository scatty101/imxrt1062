#ifndef IMXRT_DMA_HARDWARE_HPP_
#define IMXRT_DMA_HARDWARE_HPP_

#include "dma_mux.hpp"

#include "reg.hpp"
#include "clocks.hpp"

namespace imxdrivers
{
    using dma_hw_t = DMA_Type *;
    static const dma_hw_t dma_ = DMA0;

    class dma_clock_spec_t : public default_spec_t<dma_hw_t>
    {
    public:
        using default_spec_t<dma_hw_t>::default_spec_t;
    };

    class dma_hardware_t
    {
        static bool once_;
        const std::uint32_t channel_;

    public:
        dma_hardware_t(const dma_hardware_t &) = delete;
        dma_hardware_t &operator=(const dma_hardware_t &) = delete;

        dma_hardware_t(const std::uint32_t &channel) noexcept;
        ~dma_hardware_t();
        inline void set_request() noexcept
        {
            reg_write(dma_->SERQ, DMA_SERQ_SERQ(channel_));
        }
        inline void clear_request() noexcept
        {
            reg_write(dma_->CERQ, DMA_CERQ_CERQ(channel_));
        }
        inline bool hw_request() noexcept
        {
            return reg_get_bit(dma_->HRS, DMA_HRS_HRS0_MASK << channel_);
        }
        inline bool request_enabled() noexcept
        {
            return reg_get_bit(dma_->ERQ, channel_);
        }
        inline bool done() noexcept
        {
            return reg_get_bit(dma_->TCD[channel_].CSR, DMA_CSR_DONE_SHIFT);
        }

        inline void clear_done() noexcept
        {
            reg_write(dma_->CDNE, DMA_CDNE_CDNE(channel_));
        }

        inline bool active() noexcept
        {
            return reg_get_bit(dma_->TCD[channel_].CSR, DMA_CSR_ACTIVE_SHIFT);
        }

        inline void start() noexcept
        {
            reg_write(dma_->SSRT, DMA_SSRT_SSRT(channel_));
        }

        inline std::uint16_t citer() noexcept
        {
            return reg_get(dma_->TCD[channel_].CITER_ELINKNO);
        }

        inline std::uint16_t biter() noexcept
        {
            return reg_get(dma_->TCD[channel_].BITER_ELINKNO);
        }

        inline void set_csr(const std::uint16_t &csr) noexcept
        {
            reg_write(dma_->TCD[channel_].CSR, csr);
        }

        inline void set_saddr(const std::uint32_t &saddr) noexcept
        {
            reg_write(dma_->TCD[channel_].SADDR, saddr);
        }
        inline void set_daddr(const std::uint32_t &daddr) noexcept
        {
            reg_write(dma_->TCD[channel_].DADDR, daddr);
        }
        inline void set_attr(const std::uint16_t &attr) noexcept
        {
            reg_write(dma_->TCD[channel_].ATTR, attr);
        }

        inline void set_soff(const std::uint16_t &soff) noexcept
        {
            reg_write(dma_->TCD[channel_].SOFF, soff);
        }
        inline void set_doff(const std::uint16_t &doff) noexcept
        {
            reg_write(dma_->TCD[channel_].DOFF, doff);
        }
        inline void set_nbytes(const std::uint32_t &nbytes) noexcept
        {
            reg_write(dma_->TCD[channel_].NBYTES_MLNO, nbytes);
        }
        inline void set_citer(const std::uint16_t &citer) noexcept
        {
            reg_write(dma_->TCD[channel_].CITER_ELINKNO, citer);
        }
        inline void set_biter(const std::uint16_t &biter) noexcept
        {
            reg_write(dma_->TCD[channel_].BITER_ELINKNO, biter);
        }
        inline void set_dlast(const std::uint32_t &dlast_sga) noexcept
        {
            reg_write(dma_->TCD[channel_].DLAST_SGA, dlast_sga);
        }
        inline void set_slast(const std::uint32_t &slast) noexcept
        {
            reg_write(dma_->TCD[channel_].SLAST, slast);
        }

    private:
        void enable_clock() noexcept;
    };

} // namespace imxdrivers

#endif // IMXRT_DMA_HARDWARE_HPP_