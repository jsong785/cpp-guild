#pragma once

#include <list>
#include <unordered_map>
#include <utility>

class LRUCache
{
    public:
        LRUCache(const std::size_t cap);
        void set(const int key, const int val);
        int get(const int key) const;

    private:
        using CacheKv = std::pair<int, int>;
		using CacheList = std::list<CacheKv>;

        void setKv(const int key, const int val);

        const std::size_t m_capacity;
		CacheList m_cache;
		std::unordered_map<int, CacheList::iterator> m_cacheLookup;
};
