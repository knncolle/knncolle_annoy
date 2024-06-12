cmake_minimum_required(VERSION 3.14)

project(knncolle_annoy
    VERSION 0.1.0
    DESCRIPTION "knncolle bindings for Annoy"
    LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Library
add_library(knncolle_annoy INTERFACE)
add_library(knncolle::knncolle_annoy ALIAS knncolle_annoy)

target_include_directories(knncolle_annoy INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/knncolle_annoy>)
target_compile_features(knncolle_annoy INTERFACE cxx_std_17)

# Dependencies
option(KNNCOLLE_ANNOY_FETCH_EXTERN "Automatically fetch knncolle_annoy's external dependencies." ON)
if(KNNCOLLE_ANNOY_FETCH_EXTERN)
    add_subdirectory(extern)
else()
    find_package(knncolle_knncolle 2.0.0 CONFIG REQUIRED)
    find_package(Annoy CONFIG REQUIRED)
endif()

target_link_libraries(knncolle_annoy INTERFACE knncolle::knncolle Annoy::Annoy)

# Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(KNNCOLLE_ANNOY_TESTS "Build knncolle_annoy's test suite." ON)
else()
    option(KNNCOLLE_ANNOY_TESTS "Build knncolle_annoy's test suite." OFF)
endif()

if(KNNCOLLE_ANNOY_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif() 
endif()

# Install
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/knncolle_annoy)

install(TARGETS knncolle_annoy
    EXPORT knncolle_annoyTargets)

install(EXPORT knncolle_annoyTargets
    FILE knncolle_knncolle_annoyTargets.cmake
    NAMESPACE knncolle::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/knncolle_knncolle_annoy)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_annoyConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/knncolle_knncolle_annoy)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_annoyConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_annoyConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/knncolle_knncolle_annoyConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/knncolle_knncolle_annoy)
