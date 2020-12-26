#include "row_wtna.h"
#include <iomanip>
#include <ostream>

row_wtna::row_wtna(addr_type assoc) : row_base(assoc)
{
}

row_wtna::result_t row_wtna::mem_write(addr_type index)
{
    const auto it = pgmap.find(index);
    result_t r{};
    if (it == pgmap.end())
    {
        r.bf.miss = true;
    }
    r.bf.wb = true;
    return r;
}

void row_wtna::output(std::ostream &os) const
{
    auto fmt = os.flags();
    os << std::hex << std::right << std::noshowbase << std::nouppercase;
    for (const auto &t : row)
    {
        os << std::setw(sizeof(addr_type) * 2 + 2) << t;
    }
    os.setf(fmt);
}

bool row_wtna::write_policy() const
{
    return true;
}
