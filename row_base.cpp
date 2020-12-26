#include "row_base.h"

row_base::row_base(addr_type assoc) : row(assoc)
{
}

row_base::addr_type row_base::assoc() const
{
    return addr_type(row.size());
}

row_base::result_t row_base::mem_read(addr_type index)
{
    const auto it = pgmap.find(index);
    result_t r{};
    if (it == pgmap.end())
    {
        const addr_type d = replace();
        row[d] = index;
        pgmap[index] = d;
        r.bf.miss = true;
    }
    return r;
}

std::ostream &operator<<(std::ostream &os, const row_base &r)
{
    r.print(os);
    return os;
}
