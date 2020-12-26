#include "row.h"
#include "row_lfu.h"
#include "row_lru.h"
#include "row_wbwa.h"
#include "row_wtna.h"

template <typename replacement_policy, typename write_policy>
row<replacement_policy, write_policy>::row(addr_type assoc)
    : base_type(assoc), replacement_policy(assoc), write_policy(assoc)
{
}

std::unique_ptr<row_base> make_row(row_base::addr_type assoc, bool replacement_policy, bool write_policy)
{
    if (replacement_policy)
    {
        if (write_policy)
        {
            return std::make_unique<row<row_lfu, row_wtna>>(assoc);
        }
        else
        {
            return std::make_unique<row<row_lfu, row_wbwa>>(assoc);
        }
    }
    else
    {
        if (write_policy)
        {
            return std::make_unique<row<row_lru, row_wtna>>(assoc);
        }
        else
        {
            return std::make_unique<row<row_lru, row_wbwa>>(assoc);
        }
    }
}
