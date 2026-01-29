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
        reg[knncolle_annoy::annoy_prebuilt_save_name] = [](const std::filesystem::path& dir) -> knncolle::Prebuilt<int, double, double>* {
            auto scanned = knncolle_annoy::load_annoy_prebuilt_types(dir);
            if (std::strcmp(scanned.distance.c_str(), "euclidean") == 0) {
                return knncolle_annoy::load_annoy_prebuilt<int, double, double, Annoy::Euclidean>(dir);
            }
            return knncolle_annoy::load_annoy_prebuilt<int, double, double, Annoy::Manhattan>(dir);
        };
    }
};

TEST_F(AnnoyLoadPrebuiltTest, Euclidean) {
    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> ab;
    auto aptr = ab.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto dir = savedir / "euclidean";
    std::filesystem::create_directory(dir);
    aptr->save(dir);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(dir);
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

    const auto dir = savedir / "manhattan";
    std::filesystem::create_directory(dir);
    aptr->save(dir);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(dir);
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

TEST_F(AnnoyLoadPrebuiltTest, Custom) {
    knncolle_annoy::custom_save_for_annoy_index<int>() = [](const std::filesystem::path& dir) -> void {
        knncolle::quick_save(dir / "FOO", "bar", 3);
    };
    knncolle_annoy::custom_save_for_annoy_data<float>() = [](const std::filesystem::path& dir) -> void {
        knncolle::quick_save(dir / "WHEE", "stuff", 5);
    };
    knncolle_annoy::custom_save_for_annoy_distance<Annoy::Euclidean>() = [](const std::filesystem::path& dir) -> void {
        knncolle::quick_save(dir / "YAY", "blah", 4);
    };

    knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> ab;
    auto aptr = ab.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto dir = savedir / "custom";
    std::filesystem::create_directory(dir);
    aptr->save(dir);

    // Custom function is respected.
    EXPECT_EQ(knncolle::quick_load_as_string(dir / "FOO"), "bar");
    EXPECT_EQ(knncolle::quick_load_as_string(dir / "WHEE"), "stuff");
    EXPECT_EQ(knncolle::quick_load_as_string(dir / "YAY"), "blah");

    knncolle_annoy::custom_save_for_annoy_index<int>() = nullptr;
    knncolle_annoy::custom_save_for_annoy_data<float>() = nullptr;
    knncolle_annoy::custom_save_for_annoy_distance<Annoy::Euclidean>() = nullptr;

    // Everything else is still fine.
    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(dir);
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

    const auto dir = savedir / "error";
    std::filesystem::create_directory(dir);
    aptr->save(dir);

    // Deleting the index. 
    std::filesystem::remove(dir / "INDEX");

    bool failed = false;
    try {
        knncolle::load_prebuilt_shared<int, double, double>(dir);
    } catch (std::exception& e) {
        failed = true;
    }
    EXPECT_TRUE(failed);
}
