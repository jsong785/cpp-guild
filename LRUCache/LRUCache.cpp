#include "LRUCache.h"
#include <algorithm>
#include <assert.h>

LRUCache::LRUCache(const std::size_t cap) :
    m_capacity(cap)
{
}

void LRUCache::Set(const int key, const int val)
{
    SetKv(key, val);
}

void LRUCache::SetKv(const int key, const int val)
{
    auto found = std::find_if(m_cache.cbegin(), m_cache.cend(), [key](const auto &kv){
            return kv.first == key;
    });

    // handle cache hit
    if(found != m_cache.cend())
    {
        m_cache.emplace_front(found->first, val); // may fail if max size hit
        m_cache.erase(found);
    }
    // handle cache miss
    else
    {
        // just insert to the front
        if(m_cache.size() < m_capacity)
        {
            m_cache.emplace_front(key, val);
        }
        // remove least recently used and insert
        else
        {
            m_cache.pop_back();
            m_cache.emplace_front(key, val);
        }
    }
}

int LRUCache::Get(const int key) const
{
    constexpr auto NOT_FOUND_VAL = -1;

    const auto found = std::find_if(m_cache.cbegin(), m_cache.cend(), [key](const auto &kv){
            return kv.first == key;
    });
    if(found != m_cache.cend())
    {
        return found->second;
    }
    return NOT_FOUND_VAL;
}
