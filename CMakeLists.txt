cmake_minimum_required(VERSION 3.15)

project(py_tokenizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(pybind11 CONFIG REQUIRED)

# ==========================
# Common library
# ==========================
add_library(tokenizer_core STATIC
    src/provider.cpp
    src/splitter.cpp
    src/loader.cpp
    src/merger.cpp
    src/freq_finder.cpp
    engine/engine.cpp
    engine/basic_engine.cpp
)

target_include_directories(tokenizer_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(tokenizer_core PUBLIC cxx_std_17)

# ==========================
# Executable
# ==========================
add_executable(tokenizer
    main.cpp
)

target_link_libraries(tokenizer
    PRIVATE tokenizer_core
)

# ==========================
# Python module
# ==========================
pybind11_add_module(py_tokenizer
    src/binding.cpp
)

target_link_libraries(py_tokenizer
    PRIVATE tokenizer_core
)

install(TARGETS py_tokenizer
    LIBRARY DESTINATION .
)
