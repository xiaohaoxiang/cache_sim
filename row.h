#ifndef ROW_H
#define ROW_H

#include "row_base.h"
#include <memory>

template <typename replacement_policy, typename write_policy>
class row : virtual public replacement_policy, virtual public write_policy
{
  public:
    using replacement_type = replacement_policy;
    using write_type = write_policy;
    using base_type = row_base;
    using addr_type = base_type::addr_type;

  public:
    row(addr_type assoc);
};

/*
 * replacement_policy = 0 : LRU , 1 : LFU;
 * write_policy       = 0 : WBWA, 1 : WTNA;
 */
std::unique_ptr<row_base> make_row(row_base::addr_type assoc, bool replacement_policy, bool write_policy);

#endif // !ROW_H
