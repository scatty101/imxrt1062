#include "dma_channel.hpp"

#include <imxrt1062/utility.hpp>

using namespace imxutility;

namespace imxdrivers
{
    dma_channel_t::~dma_channel_t() = default;

    dma_channel_t::dma_channel_t()
    {
    }

    dma_channel_t &dma_channel_t::set_next_cfg(const dma_channel_t *const next)
    {
        if (next == nullptr)
        {
            tcd_.DLAST_SGA = 0;
            tcd_.CSR = DMA_CSR_DREQ_MASK;
        }
        else
        {
            tcd_.DLAST_SGA = r_non_cv_pointer<std::uint32_t>(&next->tcd_);
            tcd_.CSR = DMA_CSR_ESG_MASK;
        }
        return *this;
    }

    dma_channel_t &dma_channel_t::set_length(const std::uint16_t &length)
    {
        tcd_.CITER = length;
        tcd_.BITER = length;
        return *this;
    }

    std::uint16_t dma_channel_t::transfer_size(const std::uint16_t &width)
    {
        enum dma_transfer_size
        {
            transfer_1_byte = 0b000,
            transfer_2_byte = 0b001,
            transfer_4_byte = 0b010,
            transfer_8_byte = 0b011,
            transfer_32_byte = 0b101,
        };

        switch (width)
        {
        /* width 8bit */
        case 1U:
            return transfer_1_byte;
            break;
            /* width 16bit */
        case 2U:
            return transfer_2_byte;
            break;
            /* width 32bit */
        case 4U:
            return transfer_4_byte;
            break;
            /* width 64bit */
        case 8U:
            return transfer_8_byte;
            break;
            /* width 256bit */
        case 32U:
            return transfer_32_byte;
            break;
        default:
            assert(false); // Not supported transfer
            return 0;
        }
    }

} // namespace imxdrivers