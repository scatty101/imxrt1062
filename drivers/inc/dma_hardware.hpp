#ifndef IMXRT_DMA_HARDWARE_HPP_
#define IMXRT_DMA_HARDWARE_HPP_

#include "dma_mux.hpp"

#include "reg.hpp"
#include "clocks.hpp"

namespace imxdrivers
{
    using dma_hw_t = DMA_Type *;
    static const dma_hw_t dma_ = DMA0;

    /**
     * @brief Dma clock specification
     * 
     */
    class dma_clock_spec_t : public default_spec_t<dma_hw_t>
    {
    public:
        using default_spec_t<dma_hw_t>::default_spec_t;
    };

    class dma_hardware_t
    {
        const std::uint32_t channel_;

    public:
        dma_hardware_t(const dma_hardware_t &) = delete;
        dma_hardware_t &operator=(const dma_hardware_t &) = delete;

        dma_hardware_t(const std::uint32_t &channel) noexcept;
        ~dma_hardware_t();

        /**
         * @brief Hardware access to set request for channel
         * 
         */
        inline void set_request() noexcept
        {
            reg_write(dma_->SERQ, DMA_SERQ_SERQ(channel_));
        }

        /**
         * @brief Hardware access to clear request for channel
         * 
         */
        inline void clear_request() noexcept
        {
            reg_write(dma_->CERQ, DMA_CERQ_CERQ(channel_));
        }
        /**
         * @brief Hardware access to check pending hardware request on channel
         * 
         * @return true    pending hardware request
         * @return false    
         */
        inline bool hw_request() noexcept
        {
            return reg_get_bit(dma_->HRS, DMA_HRS_HRS0_MASK << channel_);
        }

        /**
         * @brief Hardware access to check software request on channel
         * 
         * @return true 
         * @return false 
         */
        inline bool request_enabled() noexcept
        {
            return reg_get_bit(dma_->ERQ, channel_);
        }
        /**
         * @brief Checks, whether channel finished transfer
         * 
         * @return true 
         * @return false 
         */
        inline bool done() noexcept
        {
            return reg_get_bit(dma_->TCD[channel_].CSR, DMA_CSR_DONE_SHIFT);
        }

        /**
         * @brief Clears channel done bit
         * 
         * It is usefull in SGA transfer - must be cleared upon setting SGA
         * 
         */
        inline void clear_done() noexcept
        {
            reg_write(dma_->CDNE, DMA_CDNE_CDNE(channel_));
        }

        /**
         * @brief Returns channel active bit
         * 
         * You shouldn't relay on this bit 
         * 
         * @return true 
         * @return false 
         */
        inline bool active() noexcept
        {
            return reg_get_bit(dma_->TCD[channel_].CSR, DMA_CSR_ACTIVE_SHIFT);
        }

        /**
         * @brief Sets start bit for channel
         * 
         */
        inline void start() noexcept
        {
            reg_write(dma_->SSRT, DMA_SSRT_SSRT(channel_));
        }

        /**
         * @brief Returns current current minor link loop value (major loop count)
         * 
         * 
         * @return std::uint16_t 
         */
        inline std::uint16_t citer() noexcept
        {
            return reg_get(dma_->TCD[channel_].CITER_ELINKNO);
        }
        /**
         * @brief Returns beginning minor link loop value(major loop count)
         * 
         * @return std::uint16_t 
         */
        inline std::uint16_t biter() noexcept
        {
            return reg_get(dma_->TCD[channel_].BITER_ELINKNO);
        }

        /**
         * @brief Sets control and status register
         * 
         * @param csr 
         */
        inline void set_csr(const std::uint16_t &csr) noexcept
        {
            reg_write(dma_->TCD[channel_].CSR, csr);
        }
        /**
         * @brief Sets source addr for transfer
         * 
         * @param saddr 
         */
        inline void set_saddr(const std::uint32_t &saddr) noexcept
        {
            reg_write(dma_->TCD[channel_].SADDR, saddr);
        }
        /**
         * @brief Set destination addr for transfer 
         * 
         * @param daddr 
         */
        inline void set_daddr(const std::uint32_t &daddr) noexcept
        {
            reg_write(dma_->TCD[channel_].DADDR, daddr);
        }
        /**
         * @brief Set the attribute for transfer - transfer sizes
         * 
         * @param attr 
         */
        inline void set_attr(const std::uint16_t &attr) noexcept
        {
            reg_write(dma_->TCD[channel_].ATTR, attr);
        }
        /**
         * @brief Set the source address offset between transfers
         * 
         * @param soff 
         */
        inline void set_soff(const std::uint16_t &soff) noexcept
        {
            reg_write(dma_->TCD[channel_].SOFF, soff);
        }

        /**
         * @brief Set the destination address offset between transfers
         * 
         * @param doff 
         */
        inline void set_doff(const std::uint16_t &doff) noexcept
        {
            reg_write(dma_->TCD[channel_].DOFF, doff);
        }

        /**
         * @brief Set bytes for single transfer
         * 
         * @param nbytes 
         */
        inline void set_nbytes(const std::uint32_t &nbytes) noexcept
        {
            reg_write(dma_->TCD[channel_].NBYTES_MLNO, nbytes);
        }

        /**
         * @brief Set current current minor link loop value (major loop count)
         * 
         * @param citer 
         */
        inline void set_citer(const std::uint16_t &citer) noexcept
        {
            reg_write(dma_->TCD[channel_].CITER_ELINKNO, citer);
        }

        /**
         * @brief Set beginning minor link loop value(major loop count)
         * 
         * @param biter 
         */
        inline void set_biter(const std::uint16_t &biter) noexcept
        {
            reg_write(dma_->TCD[channel_].BITER_ELINKNO, biter);
        }

        /**
         * @brief Set last destination address - SGA
         * 
         * @param dlast_sga 
         */
        inline void set_dlast(const std::uint32_t &dlast_sga) noexcept
        {
            reg_write(dma_->TCD[channel_].DLAST_SGA, dlast_sga);
        }

        /**
         * @brief Set the last source address adjustment
         * 
         * @param slast 
         */
        inline void set_slast(const std::uint32_t &slast) noexcept
        {
            reg_write(dma_->TCD[channel_].SLAST, slast);
        }

    private:
        void enable_clock() noexcept;
    };

} // namespace imxdrivers

#endif // IMXRT_DMA_HARDWARE_HPP_