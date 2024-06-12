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
    static void sanity_checks(const std::vector<int>& indices, const std::vector<double>& distances) {
        EXPECT_TRUE(std::is_sorted(distances.begin(), distances.end())); // sorted by increasing distance.

        auto sorted = indices;
        std::sort(sorted.begin(), sorted.end());
        EXPECT_TRUE(std::adjacent_find(sorted.begin(), sorted.end()) == sorted.end()); // all neighbors are unique.
    }

    static void sanity_checks(const std::vector<int>& indices, const std::vector<double>& distances, int k, int self) { // for finding by index
        EXPECT_EQ(indices.size(), distances.size());
        EXPECT_EQ(indices.size(), std::min(k, nobs - 1));

        for (const auto& ix : indices) { // self is not in there.
            EXPECT_TRUE(ix != self);
        }

        sanity_checks(indices, distances);
    }

protected:
    void SetUp() {
        assemble(std::get<0>(GetParam()));
    }
};

TEST_P(AnnoyTest, FindEuclidean) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Euclidean> builder;
    auto bptr = builder.build_unique(mat);
    auto bsptr = bptr->initialize();

    // Trying with a different type.
    knncolle::SimpleMatrix<int, size_t, double> mat2(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Euclidean, decltype(mat2), float, int, float> builder2;
    auto bptr2 = builder2.build_unique(mat2);
    auto bsptr2 = bptr2->initialize();

    std::vector<int> ires, ires0;
    std::vector<size_t> ires2, ires20;
    std::vector<double> dres, dres0;
    std::vector<float> dres2, dres20;

    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, k, &ires, &dres);
        sanity_checks(ires, dres, k, x);

        // Checking that NULLs work.
        bsptr->search(x, k, NULL, &dres0);
        EXPECT_EQ(dres, dres0);
        bsptr->search(x, k, &ires0, NULL);
        EXPECT_EQ(ires, ires0);

        // Checking the different types.
        bsptr2->search(x, k, &ires2, &dres2);
        EXPECT_EQ(ires.size(), ires2.size());
        EXPECT_EQ(ires.size(), dres2.size());

        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires2[j]);
            EXPECT_FLOAT_EQ(dres[j], dres2[j]);
        }

        bsptr2->search(x, k, NULL, &dres20);
        EXPECT_EQ(dres2, dres20);
        bsptr2->search(x, k, &ires20, NULL);
        EXPECT_EQ(ires2, ires20);
    }
}

TEST_P(AnnoyTest, FindManhattan) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Manhattan> builder;
    auto bptr = builder.build_unique(mat);
    auto bsptr = bptr->initialize();

    std::vector<int> ires;
    std::vector<double> dres;
    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, k, &ires, &dres);
        sanity_checks(ires, dres, k, x);
    }
}

TEST_P(AnnoyTest, QueryEuclidean) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Euclidean> builder;
    auto bptr = builder.build_unique(mat);
    auto bsptr = bptr->initialize();

    // Trying with a different type.
    knncolle::SimpleMatrix<int, size_t, double> mat2(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<Annoy::Euclidean, decltype(mat2), float, int, float> builder2;
    auto bptr2 = builder2.build_unique(mat2);
    auto bsptr2 = bptr2->initialize();

    std::vector<int> ires, ires0;
    std::vector<size_t> ires2, ires20;
    std::vector<double> dres, dres0;
    std::vector<float> dres2, dres20;

    std::mt19937_64 rng(ndim * 10 + nobs - k);
    std::vector<double> query(ndim);
    std::vector<float> fquery(ndim);

    for (int x = 0; x < nobs; ++x) {
        fill_random(query.begin(), query.end(), rng);

        bsptr->search(query.data(), k, &ires, &dres);
        EXPECT_EQ(ires.size(), std::min(k, nobs));
        EXPECT_EQ(ires.size(), dres.size());
        sanity_checks(ires, dres);

        // Checking that NULLs work.
        bsptr->search(query.data(), k, NULL, &dres0);
        EXPECT_EQ(dres, dres0);
        bsptr->search(query.data(), k, &ires0, NULL);
        EXPECT_EQ(ires, ires0);

        // Checking the different types.
        std::copy(query.begin(), query.end(), fquery.begin());
        bsptr2->search(fquery.data(), k, &ires2, &dres2);
        EXPECT_EQ(ires.size(), ires2.size());
        EXPECT_EQ(ires.size(), dres2.size());

        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires2[j]);
            EXPECT_FLOAT_EQ(dres[j], dres2[j]);
        }

        bsptr2->search(fquery.data(), k, NULL, &dres20);
        EXPECT_EQ(dres2, dres20);
        bsptr2->search(fquery.data(), k, &ires20, NULL);
        EXPECT_EQ(ires2, ires20);
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
