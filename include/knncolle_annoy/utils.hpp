#ifndef KNNCOLLE_ANNOY_UTILS_HPP
#define KNNCOLLE_ANNOY_UTILS_HPP

#include <fstream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

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
 * Numeric types for `AnnoyIndex_` and `AnnoyData_` template parameters of `AnnoyBuilder`.
 * These are typically set by `get_numeric_type()`.
 */
enum class NumericType : char {
    UINT8_T, INT8_T,
    UINT16_T, INT16_T,
    UINT32_T, INT32_T,
    UINT64_T, INT64_T,
    UNSIGNED_CHAR, SIGNED_CHAR, CHAR,
    UNSIGNED_SHORT, SHORT,
    UNSIGNED_INT, INT,
    UNSIGNED_LONG, LONG,
    UNSIGNED_LONG_LONG, LONG_LONG,
    SIZE_T, PTRDIFF_T,
    FLOAT, DOUBLE,
    UNKNOWN
};

/**
 * @tparam Type_ Some integer or floating-point type, typically used as `AnnoyIndex_` or `AnnoyData_` in `AnnoyBuilder()`.
 * @return Identity of the numeric type.
 */
template<typename Type_>
NumericType get_numeric_type() {
#ifdef UINT8_MAX
    if constexpr(std::is_same<Type_, std::uint8_t>::value) {
        return NumericType::UINT8_T;
    }
#endif
#ifdef INT8_MAX
    if constexpr(std::is_same<Type_, std::int8_t>::value) {
        return NumericType::INT8_T;
    }
#endif

#ifdef UINT16_MAX
    if constexpr(std::is_same<Type_, std::uint16_t>::value) {
        return NumericType::UINT16_T;
    }
#endif
#ifdef INT16_MAX
    if constexpr(std::is_same<Type_, std::int16_t>::value) {
        return NumericType::INT16_T;
    }
#endif

#ifdef UINT32_MAX
    if constexpr(std::is_same<Type_, std::uint32_t>::value) {
        return NumericType::UINT32_T;
    }
#endif
#ifdef INT32_MAX
    if constexpr(std::is_same<Type_, std::int32_t>::value) {
        return NumericType::INT32_T;
    }
#endif

#ifdef UINT64_MAX
    if constexpr(std::is_same<Type_, std::uint64_t>::value) {
        return NumericType::UINT64_T;
    }
#endif
#ifdef INT64_MAX
    if constexpr(std::is_same<Type_, std::int64_t>::value) {
        return NumericType::INT64_T;
    }
#endif

    if constexpr(std::is_same<Type_, unsigned char>::value) {
        return NumericType::UNSIGNED_CHAR;
    }
    if constexpr(std::is_same<Type_, signed char>::value) {
        return NumericType::SIGNED_CHAR;
    }
    if constexpr(std::is_same<Type_, char>::value) {
        return NumericType::CHAR;
    }

    if constexpr(std::is_same<Type_, unsigned short>::value) {
        return NumericType::UNSIGNED_SHORT;
    }
    if constexpr(std::is_same<Type_, short>::value) {
        return NumericType::SHORT;
    }

    if constexpr(std::is_same<Type_, unsigned int>::value) {
        return NumericType::UNSIGNED_INT;
    }
    if constexpr(std::is_same<Type_, int>::value) {
        return NumericType::INT;
    }

    if constexpr(std::is_same<Type_, unsigned long>::value) {
        return NumericType::UNSIGNED_LONG;
    }
    if constexpr(std::is_same<Type_, long>::value) {
        return NumericType::LONG;
    }

    if constexpr(std::is_same<Type_, unsigned long long>::value) {
        return NumericType::UNSIGNED_LONG_LONG;
    }
    if constexpr(std::is_same<Type_, long long>::value) {
        return NumericType::LONG_LONG;
    }

    if constexpr(std::is_same<Type_, std::size_t>::value) {
        return NumericType::SIZE_T;
    }
    if constexpr(std::is_same<Type_, std::ptrdiff_t>::value) {
        return NumericType::PTRDIFF_T;
    }

    if constexpr(std::is_same<Type_, float>::value) {
        return NumericType::FLOAT;
    }
    if constexpr(std::is_same<Type_, double>::value) {
        return NumericType::DOUBLE;
    }

    return NumericType::UNKNOWN;
}

/**
 * @brief Configuration of a saved Annoy index.
 *
 * Instances are typically created by `scan_prebuilt_save_config()`.
 */
struct PrebuiltSaveConfig {
    /**
     * Type of the index, i.e., `AnnoyIndex_` in `AnnoyBuilder()`.
     */
    NumericType index;

    /**
     * Type of the index, i.e., `AnnoyData_` in `AnnoyBuilder()`.
     */
    NumericType data;

    /**
     * Name of the distance metric, i.e., `AnnoyDistance_` in `AnnoyBuilder()`.
     */
    std::string distance;
};

/**
 * @param prefix Prefix of the file paths in which a prebuilt Annoy index was saved.
 * An Annoy index is typically saved by calling the `knncolle::Prebuilt::save()` method of the Annoy subclass instance.
 *
 * @return Configuration of the saved instance of a `knncolle::Prebuilt` Annoy subclass.
 * This is typically used to choose template parameters for `load_annoy_prebuilt()`.
 */
inline PrebuiltSaveConfig scan_prebuilt_save_config(const std::string& prefix) {
    NumericType types[2];
    knncolle::quick_load(prefix + "types", types, 2);

    PrebuiltSaveConfig config;
    config.index = types[0];
    config.data = types[1];

    const std::string distpath = prefix + "distance";
    std::ifstream input(distpath);
    config.distance.insert(config.distance.end(), (std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()) );

    return config;
}

}

#endif
