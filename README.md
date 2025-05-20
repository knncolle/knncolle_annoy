# knncolle bindings for Annoy

![Unit tests](https://github.com/knncolle/knncolle_annoy/actions/workflows/run-tests.yaml/badge.svg)
![Documentation](https://github.com/knncolle/knncolle_annoy/actions/workflows/doxygenate.yaml/badge.svg)
[![Codecov](https://codecov.io/gh/knncolle/knncolle_annoy/branch/master/graph/badge.svg)](https://codecov.io/gh/knncolle/knncolle_annoy)

## Overview

The **knncolle_annoy** library provides [**knncolle**](https://github.com/knncolle/knncolle) bindings to 
the [Annoy](https://github.com/spotify/annoy) library for approximate nearest neighbors search.
This allows users to use Annoy searches in any framework that accepts **knncolle** interfaces, sacrificing neighbor search accuracy for greater speed.
For most applications involving large datasets, this is an acceptable trade-off.

## Quick start

Instances of the various `knncolle_annoy::Annoy*` classes can be used anywhere that accepts the corresponding **knncolle** interface.
For example:

```cpp
#include "knncolle_annoy/knncolle_annoy.hpp"

int ndim = 10;
int nobs = 10000;
std::vector<double> matrix(ndim * nobs); // column-major ndim * nobs matrix.

// Wrap our data in a light SimpleMatrix.
knncolle::SimpleMatrix<int, double> mat(ndim, nobs, matrix.data());

// Build an Annoy index with Euclidean distances. 
knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> an_builder;
auto an_index = an_builder.build_unique(mat);

// Find 10 (approximate) nearest neighbors of every element.
auto results = knncolle::find_nearest_neighbors(*an_index, 10); 
```

Check out the [reference documentation](https://knncolle.github.io/knncolle_annoy/) for more details.

## Customizing the search

We can pass options to the `AnnoyBuilder` constructor:

```cpp
knncolle_annoy::AnnoyOptions an_opts;
an_opts.num_trees = 100;
an_opts.search_mult = 200; // used to compute search_k.
knncolle_annoy::AnnoyBuilder<int, double, double, Annoy::Euclidean> an_builder2(an_opts);
```

We could also modify the builder after construction:

```cpp
auto& opt = an_builder.get_options()
opt.num_trees = 100;
```

Advanced users can configure the template parameters to use more suitable types for their applications.
A hypothetical configuration is shown below with (mostly made up) reasons:

```cpp
typedef knncolle_annoy::AnnoyBuilder<
    // The type for the observation indices - perhaps int isn't big enough to
    // hold all the indices for a large dataset, so we'll use size_t.
    size_t,

    // The type for the input data, maybe we're dealing with small counts.
    uint8_t,

    // The type for the distances, maybe we'll use floats to save space.
    float,

    // The type of distance, Euclidean is so 200 BC.
    Annoy::Manhattan,

    // The type of index used internally by Annoy, guess we'll continue
    // using size_t if int wasn't big enough for us.
    size_t,

    // The type of data/distance used internally by Annoy, let's use
    // float for performance.
    float,

    // The PRNG used by Annoy, we'll stick with the default.
    Annoy::Kiss64Random,

    // The thread policy used by Annoy. I suppose we could use multi-threading.
    Annoy::AnnoyIndexSingleThreadedBuildPolicy,

    // The type of matrix that the AnnoyBuilder takes as input: forcing it
    // to be a SimpleMatrix to enable devirtualization.
    knncolle::SimpleMatrix<size_t, uint8_t>
> MyAnnoyBuilder;
```

## Building projects 

### CMake with `FetchContent`

If you're using CMake, you just need to add something like this to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
  knncolle_annoy
  GIT_REPOSITORY https://github.com/knncolle/knncolle_annoy
  GIT_TAG master # replace with a pinned release
)

FetchContent_MakeAvailable(knncolle_annoy)
```

Then you can link to **knncolle_annoy** to make the headers available during compilation:

```cmake
# For executables:
target_link_libraries(myexe knncolle::knncolle_annoy)

# For libaries
target_link_libraries(mylib INTERFACE knncolle::knncolle_annoy)
```

By default, this will use `FetchContent` to fetch all external dependencies.
Applications are advised to pin the versions of each dependency for stability - see [`extern/CMakeLists.txt`](extern/CMakeLists.txt) for suggested versions.
If you want to install them manually, use `-DKNNCOLLE_ANNOY_FETCH_EXTERN=OFF`.

### CMake with `find_package()`

```cmake
find_package(knncolle_knncolle_annoy CONFIG REQUIRED)
target_link_libraries(mylib INTERFACE knncolle::knncolle_annoy)
```

To install the library, use:

```sh
mkdir build && cd build
cmake .. -DKNNCOLLE_ANNOY_TESTS=OFF
cmake --build . --target install
```

Again, this will automatically acquire all its dependencies, see recommendations above.

### Manual

If you're not using CMake, the simple approach is to just copy the files in `include/` - either directly or with Git submodules - and include their path during compilation with, e.g., GCC's `-I`.
This will also require the external dependencies listed in [`extern/CMakeLists.txt`](extern/CMakeLists.txt). 

## Note on vectorization

Annoy will attempt to perform manual vectorization based on SSE and/or AVX instructions.
This may result in differences in the results across machines due to changes in numeric precision across architectures with varying support for SSE/AVX intrinsics.
For the most part, such differences can be avoided by consistently compiling for the "near-lowest common denominator" (such as the typical `x86-64` default for GCC and Clang) 
and ensuring that the more specific instruction subsets like SSE3 and AVX are not enabled (which are typically off by default anyway).
Nonetheless, if reproducibility across architectures is important, it can be achieved at the cost of some speed by defining the `NO_MANUAL_VECTORIZATION` macro,
which will instruct Annoy to disable its vectorized optimizations.
