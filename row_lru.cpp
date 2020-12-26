#include "row_lru.h"
#include <iterator>

row_lru::row_lru(addr_type assoc) : row_base(assoc), itmap(assoc)
{
    for (addr_type i = 0; i < assoc; i++)
    {
        itmap[i] = q.insert(q.end(), i);
    }
}

row_lru::addr_type row_lru::replace()
{
    const addr_type r = q.front();
    q.pop_front();
    return r;
}

void row_lru::update(addr_type index)
{
    q.erase(itmap[index]);
    q.push_back(index);
    itmap[index] = std::prev(q.end());
}

bool row_lru::replacement_policy() const
{
    return false;
}
