# Storing_unsigned_int_benchmark
A simple benchmark tool to compare 2 data structures, that store 16-bit unsigned integers.

The first ‹uint16_bitset› data structure is a bitvector which simply stores
65536 consecutive bits, each corresponding to a single 16-bit number
which is present (set to 1) or not present (set to 0) in the set.

Invoking ./bitset <count> - will insert <count> times 16-bit number
  and print bootstrapped time in microseconds

The second ‹nibble trie› structure is a type of a search tree. The
out-degree of each node will be 16, encoding 4 bits of the number stored. 

  Invoking ./trie <count> - will do the same with trie data structure
