#include <sstream>
#include <iostream>
#include <random>
#include "bitset.hpp"
#include "ubench.hpp"

uint16_bitset bitset;
std::vector<uint16_t> values;

int main(int argc, char **argv) {
    size_t count = 0;
    std::istringstream iss(argv[1]);
    if (!(iss >> count)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
        return 1;
    }

    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_int_distribution<> dist(0, 65535);
    for (size_t i = 0; i < count; i++) {
        values.emplace_back(dist(e));
    }

    ubench::result res = ubench::measure([]() {
        for (auto i : values)
            bitset.insert(i);
    });

    std::cout << res;
}