#include "LRUCache.h"
#include <assert.h>

LRUCache::LRUCache(const std::size_t cap) :
    m_capacity(cap)
{
}

void LRUCache::set(const int key, const int val)
{
    setKv(key, val);
}

void LRUCache::setKv(const int key, const int val)
{
	auto found = m_cacheLookup.find(key);
    // handle cache hit
    if(found != m_cacheLookup.end())
    {
        m_cache.emplace_front(found->first, val); // may fail if max size hit
		m_cacheLookup[found->first] = m_cache.begin(); // too bad it's not C++17 with the return on emplace_front
    }
    // handle cache miss
    else
    {
        // just insert to the front
        if(m_cache.size() < m_capacity)
        {
            m_cache.emplace_front(key, val);
			m_cacheLookup.insert({ key, m_cache.begin() });
        }
        // remove least recently used and insert
        else
        {
			m_cacheLookup.erase(m_cache.back().first);
            m_cache.pop_back();

            m_cache.emplace_front(key, val);
			m_cacheLookup.insert({ key, m_cache.begin() });
        }
    }
}

int LRUCache::get(const int key) const
{
    constexpr auto NOT_FOUND_VAL = -1;

	const auto found = m_cacheLookup.find(key);
    if(found != m_cacheLookup.cend())
    {
		return found->second->second;
    }
    return NOT_FOUND_VAL;
}
