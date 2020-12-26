#ifndef ROW_WBWA_H
#define ROW_WBWA_H

#include "row_base.h"
#include <iosfwd>
#include <vector>

class row_wbwa : virtual public row_base
{
  public:
    row_wbwa(addr_type assoc);
    result_t mem_write(addr_type index);
    void print(std::ostream &os) const;
    bool write_policy() const;

  private:
    std::vector<unsigned char> dirty;
};

#endif // !ROW_WBWA_H
