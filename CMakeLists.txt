cmake_minimum_required(VERSION 3.17)
project(neural_network)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(neural_network_main
        include/func.hpp
        include/idx_format.hpp
        include/matrix.tpp
        include/neural_network.hpp
        include/random.tpp
        include/utils.hpp
        src/func.cpp
        src/main.cpp
        src/neural_network.cpp
        src/utils.cpp)
add_library(neural_network
        SHARED
        include/func.hpp
        include/idx_format.hpp
        include/matrix.tpp
        include/neural_network.hpp
        include/random.tpp
        include/utils.hpp
        src/func.cpp
        src/neural_network.cpp
        src/utils.cpp)