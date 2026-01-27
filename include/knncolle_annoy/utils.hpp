#ifndef KNNCOLLE_ANNOY_UTILS_HPP
#define KNNCOLLE_ANNOY_UTILS_HPP

#include <fstream>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <functional>

#include "knncolle/knncolle.hpp"

/**
 * @file utils.hpp
 * @brief Utilities for the Annoy wrappers.
 */

namespace knncolle_annoy {

/**
 * Name to store in the `ALGORITHM` file for Annoy `knncolle::Prebuilt` instances,
 * see `knncolle::Prebuilt::save()` for details.
 */
inline static const char* save_name = "knncolle_annoy::Annoy";

/**
 * @cond
 */
template<typename Input_>
using I = std::remove_cv_t<std::remove_reference_t<Input_> >;

// Doing some SFINAE nonsense.
template<typename AnnoyDistance_, typename Other_ = int> 
struct has_name {
    static constexpr bool value = false;
};

template<typename AnnoyDistance_> 
struct has_name<AnnoyDistance_, decltype(AnnoyDistance_::name(), 0)> {
    static constexpr bool value = std::is_same<decltype(AnnoyDistance_::name()), const char*>::value;
};
/**
 * @endcond
 */

/**
 * @tparam AnnoyDistance_ An **Annoy**-compatible class to compute the distance between vectors, as used in `AnnoyBuilder()`.
 * @return Name of the distance metric, e.g., `"euclidean"`, `"manhattan"`.
 * This is taken from `AnnoyDistance_::name()` if such a method exists, otherwise `"unknown"` is returned.
 *
 * For unknown distances, consider using `customize_save_for_annoy_types()` to add more information to the on-disk representation during a `knncolle::Prebuilt::save()` call.
 */
template<typename AnnoyDistance_> 
const char* get_distance_name() { 
    if constexpr(!has_name<AnnoyDistance_>::value) {
        return "unknown";
    } else {
        return AnnoyDistance_::name();
    }
}

/**
 * Define a customized saving function to preserve type information from the Annoy index in `knncolle::Prebuilt::save()`.
 * Users can provide their own function here, to handle types that are unknown to `knncolle::get_numeric_type()` or `get_distance_name()`.
 * Any modifications to this function are not thread-safe and should be done in a serial section. 
 *
 * @tparam AnnoyDistance_ An **Annoy**-compatible class to compute the distance between vectors. 
 * @tparam AnnoyIndex_ Integer type for the observation indices in the Annoy index.
 * @tparam AnnoyData_ Floating-point type for data in the Annoy index.
 *
 * @return A global function for saving information about `AnnoyDistance_`, `AnnoyIndex_` and `AnnoyData_`.
 * If set, this will be called by the `knncolle::Prebuilt::save()` method for the Annoy `Prebuilt` subclass.
 */
template<class AnnoyDistance_, typename AnnoyIndex_, typename AnnoyData_>
std::function<void(const std::string&)>& customize_save_for_annoy_types() {
    static std::function<void(const std::string&)> fun;
    return fun;
}

}

#endif
