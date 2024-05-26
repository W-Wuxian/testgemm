cmake_minimum_required(VERSION 3.9)
project(tgutils VERSION 1.0.1 DESCRIPTION "tgutils test gemm utilities")
include(GNUInstallDirs)

add_library(tgutils SHARED src/tgutils.c)

target_include_directories(tgutils PRIVATE include)
include_directories(include)

set_target_properties(tgutils PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER include/datatype.h)

install(TARGETS tgutils
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#cmake -B ~/Work/TEST/gemm/TG/LIBTG/build/ -DCMAKE_INSTALL_PREFIX=~/Work/TEST/gemm/TG/LIBTG/build/install
#cmake --build ./build
#cmake --install ./build

#https://cmake.org/cmake/help/v3.17/guide/tutorial/index.html
#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://cgold.readthedocs.io/en/latest/tutorials/libraries/static-shared.html