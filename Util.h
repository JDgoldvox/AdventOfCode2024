#pragma once
#include <functional>
#include <utility>

class Util
{

};

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = std::hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = std::hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
            ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                + (hash1 >> 2));
    }
};