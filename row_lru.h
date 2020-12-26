#ifndef ROW_LRU_H
#define ROW_LRU_H

#include "row_base.h"
#include <list>
#include <vector>

class row_lru : virtual public row_base
{
  public:
    row_lru(addr_type assoc);
    addr_type [[nodiscard]] replace();
    void update(addr_type index);
    bool replacement_policy() const;

  private:
    std::list<addr_type> q;
    std::vector<std::list<addr_type>::const_iterator> itmap;
};

#endif // !ROW_LRU_H
