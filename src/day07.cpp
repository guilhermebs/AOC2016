#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>

void solve_pt1()
{
    std::ifstream file("inputs/day07");
    std::string line;
    int sol_pt1 = 0;
    while (getline(file, line))
    {
        bool can_match = false;
        bool is_hyper = false;
        for (size_t i = 0; i < line.size() - 3; i++)
            {
                is_hyper |= line[i] == '[';
                is_hyper ^= line[i] == ']';
                if(line[i] == line[i+3] && line[i+1] == line[i+2] && line[i] != line[i+1])
                {
                    if (is_hyper)
                    {
                        can_match = false;
                        break;
                    }
                    else
                    {
                        can_match = true;
                    }
                }
            }
        sol_pt1 += can_match;
       
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
}

void solve_pt2()
{
    std::ifstream file("inputs/day07");
    std::string line;
    int sol_pt2 = 0;
    while (getline(file, line))
    {
        std::unordered_set<std::string> aba;
        std::unordered_set<std::string> bab;
        bool is_hyper = false;
        for (size_t i = 0; i < line.size() - 2; i++)
        {
            is_hyper |= line[i] == '[';
            is_hyper ^= line[i] == ']';
            if (line[i] == line[i+2] && line[i] != line[i+1] && line[i+1] != '[' && line[i+1] != ']')
            {
                if (is_hyper)
                    bab.insert(std::string({line[i+1], line[i]}));
                else
                    aba.insert(std::string({line[i], line[i+1]}));
            }
        }
        for (const auto &s1: aba)
        {
            if (bab.contains(s1))
            {
                sol_pt2 += 1;
                break;
            }
        }
    }
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;

}
 
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}