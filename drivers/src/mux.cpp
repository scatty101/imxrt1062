#include "mux.hpp"

#include <imxrt1062/hardware.hpp>
#include <imxrt1062/utility.hpp>

#include <drivers/fsl_iomuxc.h>

namespace imxdrivers
{
    std::uint32_t pad_config_t::config_value() const noexcept
    {
        std::uint32_t cfg = IOMUXC_SW_PAD_CTL_PAD_SRE(imxutility::enum_value(slew_rate)) |
                            IOMUXC_SW_PAD_CTL_PAD_DSE(imxutility::enum_value(drive_strength)) |
                            IOMUXC_SW_PAD_CTL_PAD_SPEED(imxutility::enum_value(speed)) |
                            IOMUXC_SW_PAD_CTL_PAD_ODE(imxutility::enum_value(open_drain_enable)) |
                            IOMUXC_SW_PAD_CTL_PAD_PKE(imxutility::enum_value(pull_keep_enable)) |
                            IOMUXC_SW_PAD_CTL_PAD_PUE(imxutility::enum_value(pull_keep_select)) |
                            IOMUXC_SW_PAD_CTL_PAD_PUS(imxutility::enum_value(pull)) |
                            IOMUXC_SW_PAD_CTL_PAD_HYS(imxutility::enum_value(hyst));

        return cfg;
    }

    pin_mux_t::pin_mux_t(const mux_config_t &mux_config, const pad_config_t &pad_config) noexcept : mux_cfg_(mux_config), pad_cfg_(pad_config)
    {
        this->pad_config();
        mux();
    }

    pin_mux_t::~pin_mux_t() = default;

    void pin_mux_t::mux() const noexcept
    {
        IOMUXC_SetPinMux(mux_cfg_.mux[0], mux_cfg_.mux[1], mux_cfg_.mux[2], mux_cfg_.mux[3], mux_cfg_.mux[4], mux_cfg_.input_path);
    }

    void pin_mux_t::pad_config() const noexcept
    {
        IOMUXC_SetPinConfig(mux_cfg_.mux[0], mux_cfg_.mux[1], mux_cfg_.mux[2], mux_cfg_.mux[3], mux_cfg_.mux[4], pad_cfg_.config_value());
    }
} // namespace imxdrivers