#ifndef ROW_BASE_H
#define ROW_BASE_H

#include <cstdint>
#include <iosfwd>
#include <unordered_map>
#include <vector>

class row_base
{
  public:
    using addr_type = uint32_t;
    union result_t {
        struct
        {
            bool miss : 1;
            bool wb : 1;
        } bf;
        unsigned char val;
    };

  public:
    row_base(addr_type assoc);
    virtual ~row_base() = default;

    addr_type assoc() const;
    result_t mem_read(addr_type index);
    virtual result_t mem_write(addr_type index) = 0;
    virtual addr_type [[nodiscard]] replace() = 0;
    virtual void update(addr_type index) = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual bool replacement_policy() const = 0;
    virtual bool write_policy() const = 0;

  protected:
    std::vector<addr_type> row;
    std::unordered_map<addr_type, addr_type> pgmap;
};

std::ostream &operator<<(std::ostream &os, const row_base &r);

#endif // !ROW_BASE_H
