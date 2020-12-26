#include "row_base.h"

row_base::row_base(addr_type assoc) : row(assoc)
{
}

row_base::addr_type row_base::assoc() const
{
    return addr_type(row.size());
}

std::ostream &operator<<(std::ostream &os, const row_base &r)
{
    r.output(os);
    return os;
}
