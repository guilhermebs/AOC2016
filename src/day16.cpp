#include <chrono>
#include <iostream>
#include <tuple>
#include <bitset>


void solve_pt1()
{
    const size_t LEN = 35651584;//272;
    std::string init_bits("01000100010010111");
    //const size_t LEN = 20;
    //std::string init_bits("10000");
    std::reverse(init_bits.begin(), init_bits.end());
    std::bitset<LEN> bits(init_bits);
    auto cur_len = init_bits.size();
    for (size_t i = 0; i < cur_len; i++)
    {
        std::cout << bits[i];
    }
    std::cout << std::endl; 
    while (cur_len < LEN)
    {
        for (size_t i = 0; i < cur_len; i++)
        {
            if(cur_len + 1 + i < LEN)
                bits[cur_len + 1 + i] = !bits[cur_len - i - 1];
        }
        cur_len = std::min(cur_len * 2 + 1, LEN);
    }
    while (cur_len % 2 == 0)
    {
        for (size_t i = 0; i < cur_len/2; i++)
        {
            bits[i] = !(bits[2*i]^bits[2*i + 1]);
        }
        cur_len /= 2;
    }
    for (size_t i = 0; i < cur_len; i++)
    {
        std::cout << bits[i];
    }
    std::cout << std::endl; 
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}