#ifndef KNNCOLLE_ANNOY_HPP
#define KNNCOLLE_ANNOY_HPP

#include <vector>
#include <type_traits>

#include "knncolle/knncolle.hpp"
#include "annoy/annoylib.h"
#include "annoy/kissrandom.h"

/**
 * @file knncolle_annoy.hpp
 *
 * @brief Approximate nearest neighbor search with Annoy.
 */

namespace knncolle_annoy {

/**
 * @brief Options for `AnnoyBuilder()` and `AnnoyPrebuilt()`.
 */
struct AnnoyOptions {
    /**
     * Number of trees to construct.
     * Larger values improve accuracy at the cost of index size (i.e., memory usage), see [here](https://github.com/spotify/annoy#tradeoffs) for details.
     */
    int num_trees = 50;

    /**
     * Factor that is multiplied by the number of neighbors `k` to determine the number of nodes to search in `find_nearest_neighbors()`.
     * Larger values improve accuracy at the cost of runtime, see [here](https://github.com/spotify/annoy#tradeoffs) for details.
     * If set to -1, it defaults to `num_trees`.
     */
    double search_mult = -1;
};

template<class Distance_, typename Dim_, typename Index_, typename Float_, typename InternalIndex_, typename InternalData_>
class AnnoyPrebuilt;

/**
 * @brief Searcher on an Annoy index.
 *
 * Instances of this class are usually constructed using `AnnoyPrebuilt::initialize()`.
 *
 * @tparam Distance_ An **Annoy**-derived class to compute the distance between vectors.
 * @tparam Dim_ Integer type for the number of dimensions.
 * @tparam Index_ Integer type for the indices.
 * @tparam Float_ Floating point type for the query data and output distances.
 * @tparam InternalIndex_ Integer type for the internal indices in Annoy.
 * @tparam InternalData_ Floating point type for the internal data in Annoy.
 */
template<class Distance_, typename Dim_, typename Index_, typename Float_, typename InternalIndex_, typename InternalData_>
class AnnoySearcher : public knncolle::Searcher<Index_, Float_> {
private:
    const AnnoyPrebuilt<Distance_, Dim_, Index_, Float_, InternalIndex_, InternalData_>* my_parent;
    std::vector<InternalIndex_> my_indices;
    std::vector<InternalData_> my_distances;

    static constexpr bool same_internal = std::is_same<Float_, InternalData_>::value;
    typename std::conditional<!same_internal, std::vector<InternalData_>, bool>::type my_buffer;

    int get_search_k(int k) const {
        if (my_parent->my_search_mult < 0) {
            return -1;
        } else {
            return my_parent->my_search_mult * k + 0.5; // rounded up.
        }
    }

public:
    /**
     * @cond
     */
    AnnoySearcher(const AnnoyPrebuilt<Distance_, Dim_, Index_, Float_, InternalIndex_, InternalData_>* parent) : my_parent(parent) {
        if constexpr(!same_internal) {
            my_buffer.resize(my_parent->my_dim);
        }
    }
    /**
     * @endcond
     */

public:
    void search(Index_ i, Index_ k, std::vector<std::pair<Index_, Float_> >& output) {
        Index_ kp1 = k + 1;
        my_indices.clear();
        my_indices.reserve(kp1);
        my_distances.clear();
        my_distances.reserve(kp1);
        my_parent->my_index.get_nns_by_item(i, kp1, get_search_k(kp1), &my_indices, &my_distances); // +1, as it forgets to discard 'self'.

        output.clear();
        output.reserve(k);
        bool self_found = false;
        for (size_t x = 0, end = my_indices.size(); x < end; ++x) {
            if (!self_found && my_indices[x] == i) {
                self_found = true;
            } else {
                output.emplace_back(my_indices[x], my_distances[x]);
            }
        }

        // Just in case we're full of ties at duplicate points, such that 'c'
        // is not in the set.  Note that, if self_found=false, we must have at
        // least 'K+2' points for 'c' to not be detected as its own neighbor.
        // Thus there is no need to worry whether we are popping off a non-'c'
        // element and then returning fewer elements than expected.
        if (!self_found) {
            output.pop_back();
        }
    }
        
    void search(const Float_* query, Index_ k, std::vector<std::pair<Index_, Float_> >& output) {
        my_indices.clear();
        my_indices.reserve(k);
        my_distances.clear();
        my_distances.reserve(k);

        if constexpr(same_internal) {
            my_parent->my_index.get_nns_by_vector(query, k, get_search_k(k), &my_indices, &my_distances);
        } else {
            std::copy_n(query, my_parent->my_dim, my_buffer.begin());
            my_parent->my_index.get_nns_by_vector(my_buffer.data(), k, get_search_k(k), &my_indices, &my_distances);
        }

        output.clear();
        output.reserve(k);
        for (size_t x = 0, end = my_indices.size(); x < end; ++x) {
            output.emplace_back(my_indices[x], my_distances[x]);
        }
    }
};

/**
 * @brief Prebuilt index for an Annoy search.
 *
 * Instances of this class are usually constructed using `AnnoyBuilder::build_raw()`.
 * The `initialize()` method will create an instance of the `AnnoySearcher` class.
 *
 * @tparam Distance_ An **Annoy**-derived class to compute the distance between vectors.
 * @tparam Dim_ Integer type for the number of dimensions.
 * For the output of `AnnoyBuilder::build_raw()`, this is set to `Matrix_::dimension_type`.
 * @tparam Index_ Integer type for the indices.
 * For the output of `AnnoyBuilder::build_raw()`, this is set to `Matrix_::index_type`.
 * @tparam Float_ Floating point type for the query data and output distances.
 * @tparam InternalIndex_ Integer type for the internal indices in Annoy.
 * @tparam InternalData_ Floating point type for the internal data in Annoy.
 */
template<class Distance_, typename Dim_, typename Index_, typename Float_, typename InternalIndex_, typename InternalData_>
class AnnoyPrebuilt : public knncolle::Prebuilt<Dim_, Index_, Float_> {
public:
    /**
     * @cond
     */
    template<class Matrix_>
    AnnoyPrebuilt(const Matrix_& data, const AnnoyOptions& options) :
        my_dim(data.num_dimensions()),
        my_obs(data.num_observations()),
        my_search_mult(options.search_mult),
        my_index(my_dim)
    {
        typedef typename Matrix_::data_type Data_;
        auto work = data.create_workspace();
        if constexpr(std::is_same<Data_, InternalData_>::value) {
            for (Index_ i = 0; i < my_obs; ++i) {
                auto ptr = data.get_observation(work);
                my_index.add_item(i, ptr);
            }
        } else {
            std::vector<InternalData_> incoming(my_dim);
            for (Index_ i = 0; i < my_obs; ++i) {
                auto ptr = data.get_observation(work);
                std::copy_n(ptr, my_dim, incoming.begin());
                my_index.add_item(i, incoming.data());
            }
        }

        my_index.build(options.num_trees);
        return;
    }
    /**
     * @endcond
     */

private:
    Dim_ my_dim;
    Index_ my_obs;
    double my_search_mult;
    Annoy::AnnoyIndex<InternalIndex_, InternalData_, Distance_, Annoy::Kiss64Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy> my_index;

    friend class AnnoySearcher<Distance_, Dim_, Index_, Float_, InternalIndex_, InternalData_>;

public:
    Dim_ num_dimensions() const {
        return my_dim;
    }

    Index_ num_observations() const {
        return my_obs;
    }

    std::unique_ptr<knncolle::Searcher<Index_, Float_> > initialize() const {
        return std::make_unique<AnnoySearcher<Distance_, Dim_, Index_, Float_, InternalIndex_, InternalData_> >(this);
    }
};

/**
 * @brief Perform an approximate nearest neighbor search with Annoy.
 *
 * In the Approximate Nearest Neighbors Oh Yeah (Annoy) algorithm, a tree is constructed where a random hyperplane splits the points into two subsets at each internal node.
 * Leaf nodes are defined when the number of points in a subset falls below a threshold (close to twice the number of dimensions for the settings used here).
 * Multiple trees are constructed in this manner, each of which is different due to the random choice of hyperplanes.
 * For a given query point, each tree is searched to identify the subset of all points in the same leaf node as the query point. 
 * The union of these subsets across all trees is exhaustively searched to identify the actual nearest neighbors to the query.
 *
 * The `build_raw()` method will create an instance of the `AnnoyPrebuilt` class.
 *
 * @see
 * Bernhardsson E (2018).
 * Annoy.
 * https://github.com/spotify/annoy
 *
 * @tparam Distance_ An **Annoy**-derived class to compute the distance between vectors.
 * Note that this is not the same as `knncolle::MockDistance`.
 * @tparam Matrix_ Matrix-like object satisfying the `knncolle::MockMatrix` interface.
 * @tparam Float_ Floating point type for the query data and output distances.
 * @tparam InternalIndex_ Integer type for the internal indices in Annoy.
 * @tparam InternalData_ Floating point type for the internal data in Annoy.
 * This defaults to a `float` instead of a `double` to sacrifice some accuracy for performance.
 */
template<class Distance_, class Matrix_ = knncolle::SimpleMatrix<int, int, double>, typename Float_ = double, typename InternalIndex_ = typename Matrix_::index_type, typename InternalData_ = float>
class AnnoyBuilder : public knncolle::Builder<Matrix_, Float_> {
private:
    AnnoyOptions my_options;

public:
    /**
     * @param options Further options for Annoy index construction and searching.
     */
    AnnoyBuilder(AnnoyOptions options) : my_options(std::move(options)) {}

    /**
     * Default constructor.
     */
    AnnoyBuilder() = default;

public:
    knncolle::Prebuilt<typename Matrix_::dimension_type, typename Matrix_::index_type, Float_>* build_raw(const Matrix_& data) const {
        return new AnnoyPrebuilt<Distance_, typename Matrix_::dimension_type, typename Matrix_::index_type, Float_, InternalIndex_, InternalData_>(data, my_options);
    }
};

}

#endif
