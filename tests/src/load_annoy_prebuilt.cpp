#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include <filesystem>

#include "knncolle_annoy/load_annoy_prebuilt.hpp"

#include "TestCore.h"

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
