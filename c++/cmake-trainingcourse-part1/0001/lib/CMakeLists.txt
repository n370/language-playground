add_library(lib)

target_sources(lib
  PRIVATE
    lib.cpp

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/lib.hpp
)
