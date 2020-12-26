#ifndef CACHE_H
#define CACHE_H

#include "row.h"
#include <iosfwd>
#include <memory>
#include <vector>

class cache
{
  public:
    using addr_type = row_base::addr_type;
    using result_t = row_base::result_t;

  public:
    cache(addr_type cache_size, addr_type block_size, addr_type assoc, bool replacement_policy, bool write_policy);
    result_t mem_read(addr_type addr);
    result_t mem_write(addr_type addr);
    void output(std::ostream &os) const;

  private:
    std::vector<std::unique_ptr<row_base>> che;
    const int index_bits;
    const int tag_bits;
};

#endif // !CACHE_H
