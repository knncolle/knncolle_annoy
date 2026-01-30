include(FetchContent)

FetchContent_Declare(
  knncolle
  GIT_REPOSITORY https://github.com/knncolle/knncolle
  GIT_TAG master # ^3.1.0
)

FetchContent_Declare(
  sanisizer 
  GIT_REPOSITORY https://github.com/LTLA/sanisizer
  GIT_TAG master # ^0.1.5
)


FetchContent_Declare(
  Annoy 
  GIT_REPOSITORY https://github.com/spotify/Annoy
  GIT_TAG main # ^1.17.0
)

FetchContent_MakeAvailable(knncolle)
FetchContent_MakeAvailable(Annoy)
