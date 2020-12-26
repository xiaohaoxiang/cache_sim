#include "cache.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using addr_type = row_base::addr_type;

int main(int argc, char const *argv[])
{
    if (argc < 7)
    {
        return 1;
    }
    addr_type L1_block_size = std::strtoull(argv[1], nullptr, 0);
    addr_type L1_size = std::strtoull(argv[2], nullptr, 0);
    addr_type L1_assoc = std::strtoull(argv[3], nullptr, 0);
    bool L1_replacement_policy = *argv[4] == '1';
    bool L1_write_policy = *argv[5] == '1';
    std::string trace_file(argv[6]);

    cache che(L1_size, L1_block_size, L1_assoc, L1_replacement_policy, L1_write_policy);

    using std::cout;
    using std::endl;

    cout << std::right << std::dec << std::noboolalpha
         << "===== Simulator configuration =====\n"
            "L1_BLOCKSIZE:         "
         << std::setw(13) << L1_block_size << '\n'
         << "L1_SIZE:              " << std::setw(13) << L1_size << '\n'
         << "L1_ASSOC:             " << std::setw(13) << L1_assoc << '\n'
         << "L1_REPLACEMENT_POLICY:" << std::setw(13) << L1_replacement_policy << '\n'
         << "L1_WRITE_POLICY:      " << std::setw(13) << L1_write_policy << '\n'
         << "trace_file:           " << std::setw(13) << trace_file << '\n'
         << "===================================\n\n"
            "===== L1 contents =====\n";

    std::string tce;
    std::size_t read_count = 0, read_miss = 0, write_count = 0, write_miss = 0, wb_count = 0;
    for (std::ifstream in(trace_file); std::getline(in, tce);)
    {
        if (tce.empty())
        {
            continue;
        }

        addr_type addr = std::strtoull(tce.c_str() + 1, nullptr, 16);
        if (tce[0] == 'r')
        {
            read_count++;
            auto r = che.mem_read(addr);
            if (r.bf.miss)
            {
                read_miss++;
            }
            if (r.bf.wb)
            {
                wb_count++;
            }
        }
        else if (tce[0] == 'w')
        {
            write_count++;
            auto r = che.mem_write(addr);
            if (r.bf.miss)
            {
                write_miss++;
            }
            if (r.bf.wb)
            {
                wb_count++;
            }
        }
    }

    return 0;
}
