#include <cstdint>
#include <bitset>

class uint16_bitset {
    std::bitset<65536> data_;
public:
    uint16_bitset() = default;

    void insert(uint16_t v) {
        data_.set(v, true);
    }

    template<class T>
    void merge(const T &other) {
        data_ |= other.data();
    }

    bool has(uint16_t v) const {
        return data_[v];
    }

    void erase(uint16_t v) {
        data_[v] = false;
    }

    void intersect(const uint16_bitset &o) {
        data_ &= o.data();
    }

    std::bitset<65536> data() const {
        return data_;
    }
};