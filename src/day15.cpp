#include <chrono>
#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>

void solve_pt1()
{
    //std::vector<std::tuple<int, int>> disks{{5, 4}, {2, 1}};
    std::vector<std::tuple<int, int>> disks{{5, 2}, {13, 7}, {17, 10}, {3, 2}, {19, 9}, {7, 0}, {11, 0}};
    int t = 0;
    bool passes = false;
    while (!passes)
    {
        int offset = 1;
        passes = true;
        for (const auto &[period, phase]: disks)
        {
            if ((phase + t + offset) % period != 0)
            {
                passes = false;
                break;
            }
            offset++;
        }
        t++;
    }
    t--;
    std::cout << "Part 1 solution: " << t << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}