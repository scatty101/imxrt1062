#ifndef IMXRTDRIVERS_MUX_HPP_
#define IMXRTDRIVERS_MUX_HPP_

#include <cstdint>
#include <array>

#include <drivers/fsl_iomuxc.h>

namespace imxdrivers
{
    enum class hysterisis_t
    {
        disabled = 0b0,
        enabled = 0b1,
    };

    enum class pull_t
    {
        pulldown_100k = 0b00,
        pullup_47k = 0b01,
        pullup_100k = 0b10,
        pullup_22k = 0b11,
    };

    enum class pull_keep_select_t
    {
        keeper = 0b0,
        pull = 0b1,
    };

    enum class pull_keep_enable_t
    {
        disabled = 0b0,
        enabled = 0b1,
    };

    enum class open_drain_t
    {
        disabled = 0b0,
        enabled = 0b1,
    };

    enum class pin_speed_t
    {
        low_50MHz = 0b00,
        medium_100MHz = 0b01,
        fast_150MHz = 0b10,
        max_200MHz = 0b11,
    };

    enum class drive_strength_t
    {
        disabled = 0b000, /*!< disabled */
        r0_150 = 0b001,   /*!< r0_150	- 150 Ohm @ 3.3 V or 260 Ohm @ 1.8V */
        r0_2 = 0b010,     /*!< r0_2 - R0/2 */
        r0_3 = 0b011,     /*!< r0_3 - R0/3 */
        r0_4 = 0b100,     /*!< r0_4 - R0/4 */
        r0_5 = 0b101,     /*!< r0_5 - R0/5 */
        r0_6 = 0b110,     /*!< r0_6 - R0/6 */
        r0_7 = 0b111,     /*!< r0_7 - R0/7 */

    };

    /** \enum Slew rate
	 *
	 */
    enum class slew_rate_t
    {
        slow = 0b0, /*!< Slow */
        fast = 0b1, /*!< Fast */
    };

    struct pad_config_t
    {
        slew_rate_t slew_rate;
        drive_strength_t drive_strength;
        pin_speed_t speed;
        open_drain_t open_drain_enable;
        pull_keep_enable_t pull_keep_enable;
        pull_keep_select_t pull_keep_select;
        pull_t pull;
        hysterisis_t hyst;

        std::uint32_t config_value() const noexcept;
    };
    static constexpr std::uint32_t MUX_SIZE = 5;
    using iomux_config_t = std::array<std::uint32_t, MUX_SIZE>;

    struct mux_config_t
    {
        iomux_config_t mux;
        bool input_path;
    };

    class pin_mux_t
    {
        const mux_config_t mux_cfg_;
        const pad_config_t pad_cfg_;

    public:
        pin_mux_t(const pin_mux_t &) = delete;
        pin_mux_t &operator=(const pin_mux_t &) = delete;

        pin_mux_t(const mux_config_t &, const pad_config_t &) noexcept;
        ~pin_mux_t();

        void mux() const noexcept;
        void pad_config() const noexcept;
    };

} // namespace imxdrivers

#endif // IMXRTDRIVERS_MUX_HPP_