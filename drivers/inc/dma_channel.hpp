#ifndef IMXRT_DRIVERS_DMA_CHANNEL_HPP_
#define IMXRT_DRIVERS_DMA_CHANNEL_HPP_

#include <cstdint>

#include <imxrt1062/hardware.hpp>
#include <imxrt1062/utility.hpp>
#include <sdk/drivers/fsl_common.h>

#define DMA_BUFFER_SECTION(x) AT_NONCACHEABLE_SECTION(x)

namespace imxdrivers
{

    /**
     * @brief DMA TCD struct
     * 
     * Used to config every channel transfer. Just skipped useless union definitions from mcu file
     * 
     */
    struct alignas(32) dma_tcd_t
    {
        uint32_t SADDR = 0;       /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
        uint16_t SOFF = 0;        /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
        uint16_t ATTR = 0;        /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
        uint32_t NBYTES_MLNO = 0; /**< TCD Minor Byte Count (Minor Loop Mapping Disabled), array offset: 0x1008, array step: 0x20 */
        uint32_t SLAST = 0;       /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
        uint32_t DADDR = 0;       /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
        uint16_t DOFF = 0;        /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
        uint16_t CITER = 0;       /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
        uint32_t DLAST_SGA = 0;   /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
        uint16_t CSR = 0;         /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
        uint16_t BITER = 0;       /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
    };

    enum class dma_transfer_t
    {
        memory_to_memory,
        memory_to_peripheral,
        peripheral_to_peripheral,
        peripheral_to_memory,
    };
    struct dma_channel_t
    {
        dma_tcd_t tcd_;

        dma_channel_t();
        ~dma_channel_t();

        template <typename src_t, typename dst_t>
        dma_channel_t(const src_t *const src, const dst_t *const dst, const std::uint16_t &length, const dma_transfer_t &transfer, const dma_channel_t *const cfg = nullptr)
        {
            config(src, dst, length, transfer, cfg);
        }

        template <typename src_t, typename dst_t>
        void config(const src_t *const src, const dst_t *const dst, const std::uint16_t &length, const dma_transfer_t &transfer, const dma_channel_t *const cfg = nullptr)
        {
            set_src_addr(src);
            set_dst_addr(dst);
            set_length(length);
            set_transfer_type(src, dst, transfer);
            set_next_cfg(cfg);
        }

        template <typename src_t>
        dma_channel_t &set_src_addr(const src_t *const src)
        {
            tcd_.SADDR = imxutility::r_non_cv_pointer<std::uint32_t>(src);
            return *this;
        }
        template <typename dst_t>
        dma_channel_t &set_dst_addr(const dst_t *const dst)
        {
            tcd_.DADDR = imxutility::r_non_cv_pointer<std::uint32_t>(dst);
            return *this;
        }

        template <typename src_t, typename dst_t>
        dma_channel_t &set_transfer_type(const src_t *const, const dst_t *const, const dma_transfer_t &transfer)
        {
            std::uint16_t dst_size = sizeof(dst_t);
            std::uint16_t src_size = sizeof(src_t);
            std::int16_t src_offset, dst_offset;

            switch (transfer)
            {
            case dma_transfer_t::memory_to_memory:
                src_offset = static_cast<std::int16_t>(src_size);
                dst_offset = static_cast<std::int16_t>(dst_size);
                break;
            case dma_transfer_t::memory_to_peripheral:
                src_offset = static_cast<std::int16_t>(src_size);
                dst_offset = static_cast<std::int16_t>(0);
                break;
            case dma_transfer_t::peripheral_to_memory:
                src_offset = static_cast<std::int16_t>(0);
                dst_offset = static_cast<std::int16_t>(dst_size);
                break;
            case dma_transfer_t::peripheral_to_peripheral:
                src_offset = static_cast<std::int16_t>(0);
                dst_offset = static_cast<std::int16_t>(0);
                break;
            }
            tcd_.SOFF = src_offset;
            tcd_.DOFF = dst_offset;

            tcd_.SLAST = 0;
            tcd_.NBYTES_MLNO = src_size;
            tcd_.CSR = 0;

            tcd_.ATTR = DMA_ATTR_SSIZE(transfer_size(src_size)) | DMA_ATTR_DSIZE(transfer_size(dst_size));

            return *this;
        }

        dma_channel_t &set_next_cfg(const dma_channel_t *const next = nullptr);

        dma_channel_t &set_length(const std::uint16_t &length);

        std::uint16_t transfer_size(const std::uint16_t &width);
    };

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_DMA_CHANNEL_HPP_