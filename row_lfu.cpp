#include "row_lfu.h"

lfu_comp::lfu_comp(const row_lfu &c) : c(c)
{
}

bool lfu_comp::operator()(addr_type a, addr_type b) const
{
    const auto ra = c.rank[a], rb = c.rank[b];
    return ra < rb || ra == rb && a < b;
}

row_lfu::row_lfu(addr_type assoc) : row_base(assoc), rank(assoc)
{
    for (addr_type i = 0; i < assoc; i++)
    {
        q.insert(i);
    }
}

row_lfu::addr_type row_lfu::replace()
{
    const auto it = q.begin();
    addr_type d = *it;
    q.erase(it);
    rank[d]++;
    q.insert(d);
    return d;
}

void row_lfu::update(addr_type index)
{
    q.erase(index);
    rank[index]++;
    q.insert(index);
}

bool row_lfu::replacement_policy() const
{
    return true;
}
