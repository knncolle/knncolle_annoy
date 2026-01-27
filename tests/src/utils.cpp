#include <gtest/gtest.h>

#include "knncolle_annoy/utils.hpp"
#include "annoy/annoylib.h"

#include <string>

TEST(GetDistanceName, Basic) {
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<Annoy::Euclidean>()), "euclidean");
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<Annoy::Manhattan>()), "manhattan");
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<Annoy::Base>()), "unknown");
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<bool>()), "unknown");
}

TEST(SaveName, Basic) {
    EXPECT_EQ(std::string(knncolle_annoy::save_name), "knncolle_annoy::Annoy");
}
