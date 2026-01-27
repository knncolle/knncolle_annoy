#ifndef KNNCOLLE_ANNOY_LOAD_PREBUILT_HPP
#define KNNCOLLE_ANNOY_LOAD_PREBUILT_HPP

#include "utils.hpp"
#include "Annoy.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>

#include "knncolle/knncolle.hpp"

/**
 * @file load_annoy_prebuilt.hpp
 * @brief Load a prebuilt Annoy index.
 */

namespace knncolle_annoy {

/**
 * @brief Template types of a saved Annoy index.
 *
 * Instances are typically created by `load_annoy_prebuilt_types()`.
 */
struct AnnoyPrebuiltTypes {
    /**
     * Type of the index, i.e., `AnnoyIndex_` in `AnnoyBuilder()`.
     */
    NumericType index;

    /**
     * Type of the data, i.e., `AnnoyData_` in `AnnoyBuilder()`.
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
 * @return Template types of the saved instance of a `knncolle::Prebuilt` Annoy subclass.
 * This is typically used to choose template parameters for `load_annoy_prebuilt()`.
 */
inline AnnoyPrebuiltTypes load_annoy_prebuilt_types(const std::string& prefix) {
    NumericType types[2];
    knncolle::quick_load(prefix + "types", types, 2);

    AnnoyPrebuiltTypes config;
    config.index = types[0];
    config.data = types[1];
    config.distance = knncolle::quick_load_as_string(prefix + "distance");

    return config;
}

/**
 * Helper function to define a `knncolle::LoadPrebuiltFunction` for Annoy in `knncolle::load_prebuilt()`.
 *
 * In an Annoy-specific `knncolle::LoadPrebuiltFunction`,
 * users should first call `load_annoy_prebuilt_types()` to figure out the saved index's `AnnoyDistance_`, `AnnoyIndex` and `AnnoyData_`.
 * Then, they can call `load_annoy_prebuilt()` with the specified types to return a pointer to a `knncolle::Prebuilt` object.
 * This can be registered in `load_prebuilt_registry()` with the key in `knncolle_annoy::save_name`.
 * 
 * We do not automatically register a function as the user is responsible for deciding what types should be handled.
 * This avoids binary bloat from repeated instantiations of the Annoy template classes for every possible combination of types.
 * Instead, the user chooses which combinations of types can be loaded, e.g., if their application only deals with those combinations. 
 * Users may also have more information to handle unknown types from `get_numeric_type()` or unknown distances from `get_distance_name()`.
 * 
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam AnnoyDistance_ An **Annoy**-compatible class to compute the distance between vectors.
 * This should be the same as the distance reported in `AnnoyPrebuiltTypes::distance`.
 * @tparam AnnoyIndex_ Integer type for the observation indices in the Annoy index.
 * This should be the same as the type reported by `AnnoyPrebuiltTypes::index`.
 * @tparam AnnoyData_ Floating-point type for data in the Annoy index.
 * This should be the same as the type reported by `AnnoyPrebuiltTypes::data`.
 * @tparam AnnoyRng_ An **Annoy** class for random number generation.
 * This is provided for completeness and has no effect as the index is already built.
 * @tparam AnnoyThreadPolicy_ An **Annoy** class for the threadedness of Annoy index building.
 * This is provided for completeness and has no effect as the index is already built.
 *
 * @param prefix Prefix of the file paths in which a prebuilt Annoy index was saved.
 * An Annoy index is typically saved by calling the `knncolle::Prebuilt::save()` method of the Annoy subclass instance.
 *
 * @return Pointer to a `knncolle::Prebuilt` Annoy index.
 */
template<
    typename Index_,
    typename Data_,
    typename Distance_, 
    class AnnoyDistance_,
    typename AnnoyIndex_ = Index_,
    typename AnnoyData_ = float,
    class AnnoyRng_ = Annoy::Kiss64Random,
    class AnnoyThreadPolicy_ = Annoy::AnnoyIndexSingleThreadedBuildPolicy
>
auto load_annoy_prebuilt(const std::string& prefix) {
    std::size_t ndim;
    knncolle::quick_load(prefix + "num_dim", &ndim, 1);
    return new AnnoyPrebuilt<Index_, Data_, Distance_, AnnoyDistance_, AnnoyIndex_, AnnoyData_, AnnoyRng_, AnnoyThreadPolicy_>(prefix, ndim);
}

}

#endif
