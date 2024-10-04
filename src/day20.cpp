#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <regex>



void solve_pt1()
{
    std::fstream file("inputs/day20");
    std::string line;
    static std::regex re("(\\d+)\\-(\\d+)");
    std::smatch sm;
    std::vector<std::pair<long long, long long>> intervals;
    while (std::getline(file, line))
    {
        if (std::regex_match(line, sm, re))
        {
            intervals.push_back({std::stoll(sm[1]), std::stoll(sm[2])});
        }
    }
    std::stable_sort(intervals.begin(), intervals.end());
    long long cur_max = 0;
    for (size_t i = 0; i < intervals.size() - 1; i++)
    {
        cur_max = std::max(cur_max, intervals[i].second);
        if (intervals[i + 1].first > cur_max + 1)
        {
            std::cout << "Part 1 solution: " << intervals[i].second + 1 << std::endl;
            break;
        }
    }
    long long sol_pt2 = 0;
    for (size_t i = 0; i < intervals.size() - 1; i++)
    {
        cur_max = std::max(cur_max, intervals[i].second);
        if (intervals[i + 1].first > cur_max + 1)
        {
            sol_pt2 += intervals[i + 1].first - cur_max - 1;
        }
    }
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

