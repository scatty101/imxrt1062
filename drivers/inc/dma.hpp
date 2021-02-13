#ifndef IMXRT_DRIVERS_DMA_HPP_
#define IMXRT_DRIVERS_DMA_HPP_

#include <cstdint>

#include "dma_hardware.hpp"
#include "dma_channel.hpp"

namespace imxdrivers
{
    class dma_t
    {
        dma_hardware_t dma_ch_;
        bool enabled_;

    public:
        dma_t(const dma_t &) = delete;
        dma_t &operator=(const dma_t &) = delete;

        dma_t(const std::uint32_t &ch) noexcept;
        dma_t(const std::uint32_t &ch, const dma_request_source_t &src_request) noexcept;
        ~dma_t();

        void config(const dma_channel_t &cfg) noexcept;
        inline void start() noexcept
        {
            enabled_ = true;
            dma_ch_.set_request();
        }

        inline bool done() noexcept
        {
            if (busy())
            {
                enabled_ = not dma_ch_.done();
                return not enabled_;
            }
            return false;
        }
        inline bool busy() noexcept
        {
            return enabled_;
        }
    };
} // namespace imxdrivers

#endif // IMXRT_DRIVERS_DMA_HPP_