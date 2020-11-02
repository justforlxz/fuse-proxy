cmake_minimum_required(VERSION 3.13)
project(fuse-proxy VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(PkgConfig REQUIRED)

pkg_check_modules(fuse REQUIRED IMPORTED_TARGET fuse3)

set(SRCS
    src/main.cpp
    src/fuse.h
    src/fuse.cpp
    src/fuse-impl.h
    src/operations.h
    src/operations.cpp
)

add_executable(fuse-proxy ${SRCS})
target_link_libraries(fuse-proxy
    PkgConfig::fuse
)
