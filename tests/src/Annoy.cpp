#include <gtest/gtest.h>
#include "knncolle_annoy/knncolle_annoy.hpp"

#include <random>
#include <vector>

class AnnoyTest : public ::testing::TestWithParam<std::tuple<std::tuple<int, int>, int> > {
protected:
    inline static int nobs, ndim;
    inline static std::vector<double> data;
    inline static std::tuple<int, int> last_params;

protected:
    static void assemble(const std::tuple<int, int>& param) {
        if (param == last_params) {
            return;
        }
        last_params = param;

        nobs = std::get<0>(param);
        ndim = std::get<1>(param);

        std::mt19937_64 rng(nobs * 10 + ndim);
        std::normal_distribution distr;

        data.resize(nobs * ndim);
        for (auto& d : data) {
            d = distr(rng);
        }
    }

    template<class It_, class Rng_>
    static void fill_random(It_ start, It_ end, Rng_& eng) {
        std::normal_distribution distr;
        while (start != end) {
            *start = distr(eng);
            ++start;
        }
    }

protected:
    void SetUp() {
        assemble(std::get<0>(GetParam()));
    }

    static void sanity_checks(const std::vector<std::pair<int, double> >& results) {
        for (size_t i = 1; i < results.size(); ++i) { // sorted by increasing distance.
            EXPECT_TRUE(results[i].second >= results[i-1].second);
        }

        auto sorted = results;
        std::sort(sorted.begin(), sorted.end());
        for (size_t i = 1; i < sorted.size(); ++i) { // all neighbors are unique.
            EXPECT_TRUE(sorted[i].first >= sorted[i-1].first);
        }
    }

    static void sanity_checks(const std::vector<std::pair<int, double> >& results, int k, int index) { // for finding by index
        EXPECT_EQ(results.size(), std::min(k, nobs - 1));
        for (const auto& res : results) { // self is not in there.
            EXPECT_TRUE(res.first != index);
        }
        sanity_checks(results);
    }
};

TEST_P(AnnoyTest, FindEuclidean) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Euclidean> builder;
    auto bptr = builder.build_unique(mat);
    auto bsptr = bptr->initialize();

    std::vector<std::pair<int, double> > results;
    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, k, results);
        sanity_checks(results, k, x);
    }
}

TEST_P(AnnoyTest, FindManhattan) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Manhattan> builder;
    auto bptr = builder.build_unique(mat);
    auto bsptr = bptr->initialize();

    std::vector<std::pair<int, double> > results;
    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, k, results);
        sanity_checks(results, k, x);
    }
}

TEST_P(AnnoyTest, QueryEuclidean) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Manhattan> builder;
    auto bptr = builder.build_unique(mat);
    auto bsptr = bptr->initialize();

    std::mt19937_64 rng(ndim * 10 + nobs - k);
    std::vector<std::pair<int, double> > results;
    std::vector<double> query(ndim);
    for (int x = 0; x < nobs; ++x) {
        fill_random(query.begin(), query.end(), rng);
        bsptr->search(data.data() + x * ndim, k, results);
        EXPECT_EQ(results.size(), std::min(k, nobs));
        sanity_checks(results);
    }
}

INSTANTIATE_TEST_SUITE_P(
    Annoy,
    AnnoyTest,
    ::testing::Combine(
        ::testing::Combine(
            ::testing::Values(10, 500), // number of observations
            ::testing::Values(5, 20) // number of dimensions
        ),
        ::testing::Values(3, 10, 20) // number of neighbors (one is greater than # observations, to test correct limiting)
    )
);
