#include "row_wbwa.h"
#include <iomanip>
#include <ostream>

row_wbwa::row_wbwa(addr_type assoc) : row_base(assoc), dirty(assoc)
{
}

row_wbwa::result_t row_wbwa::mem_write(addr_type index)
{
    const auto it = pgmap.find(index);
    result_t r{};
    if (it == pgmap.end())
    {
        const addr_type d = replace();
        row[d] = index;
        pgmap[index] = d;
        r.bf.miss = true;
        if (dirty[d])
        {
            r.bf.wb = true;
        }
    }
    dirty[it->second] = true;
    return r;
}

void row_wbwa::print(std::ostream &os) const
{
    auto fmt = os.flags();
    os << std::hex << std::right << std::noshowbase;
    for (addr_type i = 0; i < dirty.size(); i++)
    {
        os << std::setw(sizeof(addr_type) * 2 + 2) << row[i] << (dirty[i] ? 'D' : ' ') << ' ';
    }
    os.setf(fmt);
}

bool row_wbwa::write_policy() const
{
    return false;
}
