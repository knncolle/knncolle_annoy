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
#include "knncolle/knncolle_annoy.hpp"

// Wrap our data in a light SimpleMatrix.
knncolle::SimpleMatrix<int, int, double> mat(ndim, nobs, matrix.data());

// Build an Annoy index. 
knncolle_annoy::AnnoyBuilder<Annoy::Euclidean> an_builder;
auto an_index = an_builder.build_unique(mat);

// Find 10 (approximate) nearest neighbors of every element.
auto results = knncolle::find_nearest_neighbors(*an_index, 10); 
```

We could alternate between exact and approximate searches at run-time:

```cpp
std::unique_ptr<knncolle::Prebuilt<int, int, double> > ptr;
if (use_exact) {
    knncolle::KmknnBuilder<> kbuilder;
    ptr = kbuilder.build_unique(mat);
} else {
    knncolle::AnnoyBuilder<> abuilder;
    ptr = abuilder.build_unique(mat);
}
```

We can also customize the construction of the `AnnoyBuilder` by passing in options:

```cpp
knncolle_annoy::AnnoyOptions an_opts;
an_opts.num_trees = 100;
an_opts.search_mult = 200; // used to compute search_k.
knncolle_annoy::AnnoyBuilder<> an_builder2(an_opts);
```

Check out the [reference documentation](https://knncolle.github.io/knncolle_annoy/) for more details.

## Building projects 

### CMake with `FetchContent`

If you're using CMake, you just need to add something like this to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
  knncolle
  GIT_REPOSITORY https://github.com/knncolle/knncolle_annoy
  GIT_TAG master # or any version of interest
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

By default, this will use `FetchContent` to fetch all external dependencies.
If you want to install them manually, use `-DKNNCOLLE_ANNOY_FETCH_EXTERN=OFF`.
See [`extern/CMakeLists.txt`](extern/CMakeLists.txt) to find compatible versions of each dependency.

### Manual

If you're not using CMake, the simple approach is to just copy the files in `include/` - either directly or with Git submodules - and include their path during compilation with, e.g., GCC's `-I`.
This requires the external dependencies listed in [`extern/CMakeLists.txt`](extern/CMakeLists.txt), which also need to be made available during compilation.
