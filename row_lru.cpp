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
    const addr_type d = q.front();
    q.pop_front();
    itmap[d] = q.insert(q.end(), d);
    return d;
}

void row_lru::update(addr_type index)
{
    const addr_type d = pgmap[index];
    q.erase(itmap[d]);
    itmap[d] = q.insert(q.end(), d);
}

bool row_lru::replacement_policy() const
{
    return false;
}
