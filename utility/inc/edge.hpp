#if !defined IMXRT1062_UTILITY_EDGE_H_
#define IMXRT1062_UTILITY_EDGE_H_

#include <cstdint>
namespace imxutility
{
    /**
     * @brief Simple edge detect class. 
     * 
     * Edge detection in mean of digital signal, but it can also serve as detecting change on value
     * Detection is done via XOR func.
     *       
     * @tparam T base type 
     */
    template <typename T>
    class edge_t
    {
        T last_;            /*!< Holds last value */
        bool rising_edge_;  /*!< Current state of rising edge*/
        bool falling_edge_; /*!< Current state of falling edge */

    public:
        /**
         * @brief Copy constructor is forbidden 
         * 
         */
        edge_t(const edge_t &) = delete;

        /**
         * @brief Move is forbidden
         * 
         * @return edge_t& 
         */
        edge_t &operator=(const edge_t &) = delete;

        /**
         * @brief Destroy the edge t object
         * 
         */
        ~edge_t() = default;

        /**
         * @brief Construct a new edge t object
         * 
         */
        edge_t() noexcept : last_(static_cast<T>(0)), rising_edge_(false), falling_edge_(false)
        {
        }

        /**
         * @brief Method, which should be feed with new values.
         * 
         * @param new_value 
         * @return true     if any change was detected
         * @return false    if change wasn't detected
         */
        inline bool detect(const T &new_value) noexcept
        {
            const bool any_edge = new_value ^ last_;

            rising_edge_ = any_edge and not last_;
            falling_edge_ = any_edge and last_;

            last_ = new_value;

            return any_edge;
        }

        /**
         * @brief Returns rising edge
         * 
         * @return true     if rising edge occured since last detect
         * @return false    if rising edge didn't occure since last detect
         */
        inline bool rising_edge() const noexcept
        {
            return rising_edge_;
        }
        /**
         * @brief Returns falling edge
         * 
         * @return true     if falling edge occured since last detect
         * @return false    if falling edge didn't occure since last detect
         */
        inline bool falling_edge() const noexcept
        {
            return falling_edge_;
        }
    };

} // namespace imxutility

#endif // IMXRT1062_UTILITY_EDGE_H_
