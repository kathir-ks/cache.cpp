#include <iostream>
#include <cstdint>
#include <cstring>

// MurmurHash3 32-bit implementation
uint32_t MurmurHash3_x86_32(const void *key, int len, uint32_t seed)
{
    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len / 4;
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    uint32_t h1 = seed;
    uint32_t *blocks = (uint32_t *)(data + nblocks * 4);

    // Process the data in 4-byte blocks
    for (int i = -nblocks; i; i++)
    {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15)); // Rotate left
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13)); // Rotate left
        h1 = h1 * 5 + 0xe6546b64;
    }

    // Process the remaining bytes
    const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
    uint32_t k1 = 0;
    switch (len & 3)
    {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15)); // Rotate left
        k1 *= c2;
        h1 ^= k1;
    }

    // Finalization
    h1 ^= len;
    h1 = (h1 ^ (h1 >> 16)) * 0x85ebca6b;
    h1 = (h1 ^ (h1 >> 13)) * 0xc2b2ae35;
    h1 = h1 ^ (h1 >> 16);

    return h1;
}

int main()
{
    const char *key = "Hello, MurmurHash!";
    uint32_t seed = 42;
    uint32_t hash_value = MurmurHash3_x86_32(key, std::strlen(key), seed);

    std::cout << "Hash Value: " << hash_value << std::endl;
    return 0;
}
