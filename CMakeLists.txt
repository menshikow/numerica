cmake_minimum_required(VERSION 3.15...3.29)

project(numerica
    VERSION 0.1.0
    LANGUAGES CXX
)

add_library(numerica INTERFACE)
add_library(numerica::numerica ALIAS numerica)

target_include_directories(numerica
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(numerica INTERFACE cxx_std_20)

target_compile_definitions(numerica
  INTERFACE
    NUMERICA_HEADER_ONLY=1
)

option(NUMERICA_BUILD_TESTS "Build numerica tests" ON)

if (NUMERICA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
