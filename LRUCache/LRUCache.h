#pragma once

#include <list>
#include <utility>

class LRUCache
{
    public:
        LRUCache(const std::size_t cap);
        void Set(const int key, const int val);
        int Get(const int key) const;

    private:
        using CacheKv = std::pair<int, int>;

        void SetKv(const int key, const int val);

        const std::size_t m_capacity;
        std::list<CacheKv> m_cache;
};
