#include <gtest/gtest.h>
#include "knncolle_annoy/knncolle_annoy.hpp"

#include <random>
#include <vector>
#include <filesystem>
#include <cstring>

class TestCore {
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
};

class AnnoyTest : public TestCore, public ::testing::TestWithParam<std::tuple<std::tuple<int, int>, int> > { 
protected:
    void SetUp() {
        assemble(std::get<0>(GetParam()));
    }
};

TEST_P(AnnoyTest, FindEuclidean) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> builder;
    auto bptr = builder.build_unique(mat);
    EXPECT_EQ(bptr->num_dimensions(), ndim);
    EXPECT_EQ(bptr->num_observations(), nobs);
    auto bsptr = bptr->initialize();

    // Trying with different types; mismatch between Index_ and AnnoyIndex_.
    knncolle::SimpleMatrix<size_t, double> mat2(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<size_t, double, double, Annoy::Euclidean, int> builder2;
    auto bptr2 = builder2.build_unique(mat2);
    auto bsptr2 = bptr2->initialize();

    // NO mismatch between Data_ and AnnoyData_.
    std::vector<float> fdata(data.begin(), data.end());
    knncolle::SimpleMatrix<int, float> mat3(ndim, nobs, fdata.data());
    knncolle_annoy::AnnoyBuilder<int, float, double, Annoy::Euclidean> builder3;
    auto bptr3 = builder3.build_unique(mat3);
    auto bsptr3 = bptr3->initialize();

    // NO mismatch between Distance_ and AnnoyData_.
    knncolle_annoy::AnnoyBuilder<int, double, float, Annoy::Euclidean> builder4;
    auto bptr4 = builder4.build_unique(mat);
    auto bsptr4 = bptr4->initialize();

    std::vector<int> ires, ires0;
    std::vector<size_t> ires2;
    std::vector<int> ires3, ires4;
    std::vector<double> dres, dres0;
    std::vector<double> dres2, dres3;
    std::vector<float> dres4;

    knncolle::EuclideanDistance<double, double> eucdist;

    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, k, &ires, &dres);
        sanity_checks(ires, dres, k, x);

        // Checking that NULLs work.
        bsptr->search(x, k, NULL, &dres0);
        EXPECT_EQ(dres, dres0);
        bsptr->search(x, k, &ires0, NULL);
        EXPECT_EQ(ires, ires0);

        // Checking the distance to the most distant neighbor. This needs to be a little
        // gentle w.r.t. tolerances due to differences in precision.
        {
            auto furthest = ires.back();
            auto current = data.data() + x * ndim;
            auto ptr = data.data() + furthest * ndim;
            auto expected = eucdist.raw(ndim, current, ptr);
            EXPECT_LT(std::abs(eucdist.normalize(expected) - dres.back()), 0.0001);
        }

        // Checking the different types (2)
        bsptr2->search(x, k, &ires2, &dres2);
        EXPECT_EQ(ires.size(), ires2.size());
        EXPECT_EQ(ires.size(), dres2.size());
        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires2[j]);
            EXPECT_FLOAT_EQ(dres[j], dres2[j]);
        }

        // Checking the different types (3)
        bsptr3->search(x, k, &ires3, &dres3);
        EXPECT_EQ(ires.size(), ires3.size());
        EXPECT_EQ(ires.size(), dres3.size());

        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires3[j]);
            EXPECT_FLOAT_EQ(dres[j], dres3[j]);
        }

        // Checking the different types (4)
        bsptr4->search(x, k, &ires4, &dres4);
        EXPECT_EQ(ires.size(), ires4.size());
        EXPECT_EQ(ires.size(), dres4.size());
        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires4[j]);
            EXPECT_FLOAT_EQ(dres[j], dres4[j]);
        }
    }
}

TEST_P(AnnoyTest, FindManhattan) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Manhattan> builder;
    auto bptr = builder.build_shared(mat); // make a shared pointer for some variety.
    auto bsptr = bptr->initialize();

    knncolle::ManhattanDistance<double, double> mandist;

    std::vector<int> ires;
    std::vector<double> dres;
    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, k, &ires, &dres);
        sanity_checks(ires, dres, k, x);

        // Checking the distance to the most distant neighbor. This needs to be a little
        // gentle w.r.t. tolerances due to differences in precision.
        {
            auto furthest = ires.back();
            auto current = data.data() + x * ndim;
            auto ptr = data.data() + furthest * ndim;
            auto expected = mandist.raw(ndim, current, ptr);
            EXPECT_LT(std::abs(mandist.normalize(expected) - dres.back()), 0.0001);
        }
    }
}

TEST_P(AnnoyTest, QueryEuclidean) {
    int k = std::get<1>(GetParam());    

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> builder;
    auto bptr = builder.build_known_unique(mat); // test coverage for the known override.
    auto bsptr = bptr->initialize();

    // Trying with different types; mismatch between Index_ and AnnoyIndex_.
    knncolle::SimpleMatrix<size_t, double> mat2(ndim, nobs, data.data());
    knncolle_annoy::AnnoyBuilder<size_t, double, double, Annoy::Euclidean, int> builder2;
    auto bptr2 = builder2.build_unique(mat2);
    auto bsptr2 = bptr2->initialize();

    // NO mismatch between Data_ and AnnoyData_.
    std::vector<float> fdata(data.begin(), data.end());
    knncolle::SimpleMatrix<int, float> mat3(ndim, nobs, fdata.data());
    knncolle_annoy::AnnoyBuilder<int, float, double, Annoy::Euclidean> builder3;
    auto bptr3 = builder3.build_unique(mat3);
    auto bsptr3 = bptr3->initialize();

    // NO mismatch between Distance_ and AnnoyData_.
    knncolle_annoy::AnnoyBuilder<int, double, float, Annoy::Euclidean> builder4;
    auto bptr4 = builder4.build_unique(mat);
    auto bsptr4 = bptr4->initialize();

    std::vector<int> ires, ires0;
    std::vector<size_t> ires2;
    std::vector<int> ires3, ires4;
    std::vector<double> dres, dres0;
    std::vector<double> dres2, dres3;
    std::vector<float> dres4;

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
        bsptr2->search(query.data(), k, &ires2, &dres2);
        EXPECT_EQ(ires.size(), ires2.size());
        EXPECT_EQ(ires.size(), dres2.size());
        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires2[j]);
            EXPECT_FLOAT_EQ(dres[j], dres2[j]);
        }

        std::copy(query.begin(), query.end(), fquery.begin());
        bsptr3->search(fquery.data(), k, &ires3, &dres3);
        EXPECT_EQ(ires.size(), ires3.size());
        EXPECT_EQ(ires.size(), dres3.size());
        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires3[j]);
            EXPECT_FLOAT_EQ(dres[j], dres3[j]);
        }

        bsptr4->search(query.data(), k, &ires4, &dres4);
        EXPECT_EQ(ires.size(), ires4.size());
        EXPECT_EQ(ires.size(), dres4.size());
        for (size_t j = 0; j < ires.size(); ++j) {
            EXPECT_EQ(ires[j], ires4[j]);
            EXPECT_FLOAT_EQ(dres[j], dres4[j]);
        }
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

TEST(Annoy, Constructor) {
    // Check that the overloaded constructors work.
    knncolle_annoy::AnnoyOptions opt;
    EXPECT_NE(opt.num_trees, 100);
    opt.num_trees = 100;

    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> ab(opt);
    auto& an_opt = ab.get_options();
    EXPECT_EQ(an_opt.num_trees, 100);

    // Check that assignment to the options works.
    an_opt.num_trees = 500;
    EXPECT_EQ(ab.get_options().num_trees, 500);
}

class AnnoyMiscTest : public TestCore, public ::testing::Test {
public:
    void SetUp() {
        assemble({ 100, 5 });
    }
};

TEST_F(AnnoyMiscTest, SearchMult) {
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> ab;
    auto& an_opt = ab.get_options();
    an_opt.search_mult = 20;

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    auto ptr = ab.build_known_shared(mat); // test coverage for the known override.
    auto sptr = ptr->initialize();

    std::vector<int> ires;
    std::vector<double> dres;
    sptr->search(0, 10, &ires, &dres);
    sanity_checks(ires, dres, 10, 0);
}

TEST(Annoy, Duplicates) {
    // Checking that the neighbor identification works correctly when there are
    // so many duplicates that an observation doesn't get reported by Annoy in
    // its own list of neighbors.
    int ndim = 5;
    int nobs = 100;
    std::vector<double> data(ndim * nobs);

    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> builder; 
    auto ptr = builder.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));
    auto sptr = ptr->initialize();
    std::vector<int> ires;
    std::vector<double> dres;

    // By default, AnnoyIndex_ == Index_ and AnnoyData_ != Distance_. So we
    // also test AnnoyIndex_ != Index_ and AnnoyData_ == Distance_, which uses
    // slightly different code for removing the extra observation.
    knncolle_annoy::AnnoyBuilder<size_t, double, float, Annoy::Euclidean, int, float> builder2; 
    auto ptr2 = builder2.build_unique(knncolle::SimpleMatrix<size_t, double>(ndim, nobs, data.data()));
    auto sptr2 = ptr2->initialize();
    std::vector<size_t> ires2;
    std::vector<float> dres2;

    for (int x = 0; x < nobs; ++x) {
        sptr->search(x, 10, &ires, &dres);
        EXPECT_EQ(ires.size(), 10);
        for (const auto& ix : ires) { // self is not in there.
            EXPECT_TRUE(ix != x);
        }
        EXPECT_EQ(dres.back(), 0);
        EXPECT_EQ(dres.front(), 0);

        sptr2->search(x, 10, &ires2, &dres2);
        EXPECT_EQ(ires2.size(), 10);
        for (const auto& ix : ires2) { // self is not in there.
            EXPECT_NE(ix, x);
        }
        EXPECT_EQ(dres2.back(), 0);
        EXPECT_EQ(dres2.front(), 0);
    }
}

#include "knncolle_annoy/load_annoy_prebuilt.hpp"

class AnnoyLoadPrebuiltTest : public TestCore, public ::testing::Test {
protected:
    inline static std::filesystem::path savedir;

    static void SetUpTestSuite() {
        assemble({ 50, 5 });

        savedir = "save-prebuilt-tests";
        std::filesystem::remove_all(savedir);
        std::filesystem::create_directory(savedir);

        auto& reg = knncolle::load_prebuilt_registry<int, double, double>();
        reg[knncolle_annoy::save_name] = [](const std::string& prefix) -> knncolle::Prebuilt<int, double, double>* {
            auto scanned = knncolle_annoy::scan_prebuilt_save_config(prefix);
            if (std::strcmp(scanned.distance.c_str(), "euclidean") == 0) {
                return knncolle_annoy::load_annoy_prebuilt<int, double, double, Annoy::Euclidean>(prefix);
            }
            return knncolle_annoy::load_annoy_prebuilt<int, double, double, Annoy::Manhattan>(prefix);
        };
    }
};

TEST_F(AnnoyLoadPrebuiltTest, Euclidean) {
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> ab;
    auto aptr = ab.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto prefix = (savedir / "euclidean_").string();
    aptr->save(prefix);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(prefix);
    std::vector<int> output_i, output_i2;
    std::vector<double> output_d, output_d2;

    auto searcher = aptr->initialize();
    auto researcher = reloaded->initialize();
    for (int x = 0; x < nobs; ++x) {
        searcher->search(x, 5, &output_i, &output_d);
        researcher->search(x, 5, &output_i2, &output_d2);
        EXPECT_EQ(output_i, output_i2);
        EXPECT_EQ(output_d, output_d2);
    }
}

TEST_F(AnnoyLoadPrebuiltTest, Manhattan) {
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Manhattan> ab;
    auto aptr = ab.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto prefix = (savedir / "manhattan_").string();
    aptr->save(prefix);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(prefix);
    std::vector<int> output_i, output_i2;
    std::vector<double> output_d, output_d2;

    auto searcher = aptr->initialize();
    auto researcher = reloaded->initialize();
    for (int x = 0; x < nobs; ++x) {
        searcher->search(x, 5, &output_i, &output_d);
        researcher->search(x, 5, &output_i2, &output_d2);
        EXPECT_EQ(output_i, output_i2);
        EXPECT_EQ(output_d, output_d2);
    }
}

TEST_F(AnnoyLoadPrebuiltTest, Error) {
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Manhattan> ab;
    auto aptr = ab.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto prefix = (savedir / "error_").string();
    aptr->save(prefix);

    // Deleting the index. 
    std::filesystem::remove(prefix + "index");

    bool failed = false;
    try {
        knncolle::load_prebuilt_shared<int, double, double>(prefix);
    } catch (std::exception& e) {
        failed = true;
    }
    EXPECT_TRUE(failed);
}
