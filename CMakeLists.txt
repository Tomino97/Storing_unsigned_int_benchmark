cmake_minimum_required(VERSION 3.14)
project(03)

set(CMAKE_CXX_STANDARD 17)

add_executable(bitset src/bitset.hpp src/ins-bitset.cpp src/ubench.hpp)
add_executable(trie src/ins-trie.cpp src/trie.hpp src/ubench.hpp)