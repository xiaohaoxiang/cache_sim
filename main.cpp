#include "cache.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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
            "L1_BLOCKSIZE:"
         << std::setw(22) << L1_block_size << "\nL1_SIZE:" << std::setw(27) << L1_size << "\nL1_ASSOC:" << std::setw(26)
         << L1_assoc << "\nL1_REPLACEMENT_POLICY:" << std::setw(13) << L1_replacement_policy
         << "\nL1_WRITE_POLICY:" << std::setw(19) << L1_write_policy << "\ntrace_file:" << std::setw(24) << trace_file
         << "\n===================================\n\n"
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

    auto ndec = [](double x, int n) {
        std::ostringstream oss;
        x += 0.5 * std::pow(10.0, -n);
        long a = long(std::floor(x));
        oss << a << '.';
        while (n--)
        {
            x = (x - a) * 10.0;
            a = long(std::floor(x));
            oss << a;
        }
        return oss.str();
    };

    cout << che << '\n'
         << std::right << std::dec << std::noboolalpha
         << "====== Simulation results (raw) ======"
            "\na. number of L1 reads:"
         << std::setw(16) << read_count << "\nb. number of L1 read misses:" << std::setw(10) << read_miss
         << "\nc. number of L1 writes:" << std::setw(15) << write_count
         << "\nd. number of L1 write misses:" << std::setw(9) << write_miss << "\ne. L1 miss rate:" << std::setw(22)
         << ndec(double(read_miss + write_miss) / double(read_count + write_count), 4)
         << "\nf. number of writebacks from L1:" << std::setw(6) << wb_count
         << "\ng. total memory traffic:" << std::setw(14)
         << (L1_write_policy ? read_miss + write_count : read_miss + write_miss + wb_count)
         << "\n\n==== Simulation results (performance) ===="
            "\n1. average access time:"
         << std::setw(15)
         << ndec(
                [&]() {
                    double hit = 0.25 + 2.5 * (L1_size / (512.0 * 1024.0)) + 0.025 * (L1_block_size / 16.0 + L1_assoc);
                    double miss_penalty = 20.0 + 0.5 * (L1_block_size / 16);
                    return hit + miss_penalty * (double(read_miss + write_miss) / double(read_count + write_count));
                }(),
                4)
         << " ns" << endl;

    return 0;
}
