#include <chrono>
#include <iostream>
#include <tuple>
#include <deque>
#include <array>
#include "helper.hpp"
#include <unordered_set>

const int FAV_NUMBER = 1352;

int count_ones(int n)
{
    int result = 0;
    while (n != 0)
    {
        result += n&1;
        n >>= 1;
    }
    return result;
}

bool is_wall(int x, int y)
{
    if (x < 0 || y < 0) return true;
    int n = x*x + 3*x + 2*x*y + y + y*y + FAV_NUMBER;
    return count_ones(n) & 1;
}

void solve_pt1()
{
    std::deque<std::tuple<int, int, int> > queue{{1, 1, 0}};
    std::unordered_set<std::tuple<int, int>> visited{{1, 1}};
    const int x_target = 31; const int y_target = 39;
    while (queue.size())
    {
        auto [x, y, nsteps] = queue.front();
        queue.pop_front();
        if (x == x_target && y == y_target)
        {
            std::cout << "Part 1 solution: " << nsteps << std::endl;
            break;
        }
        std::array<std::tuple<int, int>, 4> neighbours{std::tuple{x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}};
        for (auto &[xn, yn]: neighbours)
        {
            if (!is_wall(xn, yn) && !visited.contains({xn, yn}))
            {
                visited.insert({xn, yn});
                queue.push_back({xn, yn, nsteps+1});
            }
        }
    }
}

void solve_pt2()
{
    std::deque<std::tuple<int, int, int> > queue{{1, 1, 0}};
    std::unordered_set<std::tuple<int, int>> visited{{1, 1}};
    const int nsteps_max = 50;
    while (queue.size())
    {
        auto [x, y, nsteps] = queue.front();
        queue.pop_front();
        if (nsteps > nsteps_max) break;
        visited.insert({x, y});
        std::array<std::tuple<int, int>, 4> neighbours{std::tuple{x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}};
        for (auto &[xn, yn]: neighbours)
        {
            if (!is_wall(xn, yn) && !visited.contains({xn, yn}))
            {
                queue.push_back({xn, yn, nsteps+1});
            }
        }
    }
    std::cout << "Part 2 solution: " << visited.size() << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}