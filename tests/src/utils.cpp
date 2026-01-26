#include <gtest/gtest.h>

#include "knncolle_annoy/utils.hpp"
#include "annoy/annoylib.h"

#include <cstdint>
#include <cstddef>

TEST(GetNumericType, Basic) {
    // Don't do more specific tests because some compilers might have aliases
    // e.g., size_t might be a uint64_t and get reported as a UINT64_T.
    EXPECT_NE(knncolle_annoy::get_numeric_type<std::uint8_t>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<std::int8_t>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<std::uint16_t>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<std::int16_t>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<std::uint32_t>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<std::int32_t>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<std::uint64_t>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<std::int64_t>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<char>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<signed char>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<unsigned char>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<short>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<unsigned short>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<int>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<unsigned int>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<long>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<unsigned long>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<long long>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<unsigned long long>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<std::size_t>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<std::ptrdiff_t>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_NE(knncolle_annoy::get_numeric_type<float>(), knncolle_annoy::NumericType::UNKNOWN);
    EXPECT_NE(knncolle_annoy::get_numeric_type<double>(), knncolle_annoy::NumericType::UNKNOWN);

    EXPECT_EQ(knncolle_annoy::get_numeric_type<bool>(), knncolle_annoy::NumericType::UNKNOWN);
}

TEST(GetDistanceName, Basic) {
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<Annoy::Euclidean>()), "euclidean");
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<Annoy::Manhattan>()), "manhattan");
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<Annoy::Base>()), "unknown");
    EXPECT_EQ(std::string(knncolle_annoy::get_distance_name<bool>()), "unknown");
}

TEST(SaveName, Basic) {
    EXPECT_EQ(std::string(knncolle_annoy::save_name), "knncolle_annoy::Annoy");
}
