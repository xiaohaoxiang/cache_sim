#include "cache.h"
#include "utils.hpp"

cache::cache(addr_type cache_size, addr_type block_size, addr_type assoc, bool replacement_policy, bool write_policy)
    : che(cache_size / (block_size * assoc)), index_bits(log2_lowbit(block_size)),
      tag_bits(index_bits + log2_lowbit(addr_type(che.size())))
{
    for (auto &p : che)
    {
        p = make_row(assoc, replacement_policy, write_policy);
    }
}

cache::result_t cache::mem_read(addr_type addr)
{
    addr_type sn = (addr >> index_bits) & ((addr_type(1) << (tag_bits - index_bits)) - addr_type(1));
    return che[sn]->mem_read(addr >> tag_bits);
}

cache::result_t cache::mem_write(addr_type addr)
{
    addr_type sn = (addr >> index_bits) & ((addr_type(1) << (tag_bits - index_bits)) - addr_type(1));
    return che[sn]->mem_write(addr >> tag_bits);
}
