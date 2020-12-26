#ifndef ROW_LFU_H
#define ROW_LFU_H

#include "row_base.h"
#include <cstddef>
#include <set>
#include <vector>

class row_lfu;

class lfu_comp
{
  public:
    using addr_type = row_base::addr_type;

  public:
    lfu_comp(const row_lfu &c);
    bool operator()(addr_type a, addr_type b) const;

  private:
    const row_lfu &c;
};

class row_lfu : virtual public row_base
{
  public:
    row_lfu(addr_type assoc);
    addr_type replace();
    void update(addr_type index);
    bool replacement_policy() const;

  private:
    std::vector<std::size_t> rank;
    std::set<addr_type, lfu_comp> q;

    friend class lfu_comp;
};

#endif // !ROW_LFU_H
