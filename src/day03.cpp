#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include "helper.hpp"

void solve_pt1()
{
    std::ifstream file("inputs/day03");
    std::string line;
    int sol_pt1 = 0;
    while (getline(file, line))
    {
        std::array<std::string, 3> split{
            line.substr(0, 5),
            line.substr(5, 5),
            line.substr(10, 5)
        };
        std::array<int, 3> numbers;
        for (size_t i = 0; i < 3; i++)
        {
            auto s = split[i];
            s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
            numbers[i] = std::stoi(s);
        }
        std::sort(numbers.begin(), numbers.end());
        sol_pt1 += numbers[0] + numbers[1] > numbers[2];
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
}

void solve_pt2()
{
    std::ifstream file("inputs/day03");
    std::string line;
    int sol_pt2 = 0;
    std::array<int, 9> triangle_set;
    int j = 0;
    while (getline(file, line))
    {
        std::array<std::string, 3> split{
            line.substr(0, 5),
            line.substr(5, 5),
            line.substr(10, 5)
        };
        for (size_t i = 0; i < 3; i++)
        {
            auto s = split[i];
            s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
            triangle_set[i*3 + j] = std::stoi(s);
        }
        if (j == 3)
        {
            for (int i=0; i<3; i++)
            {
                std::sort(triangle_set.begin() + 3 * i, triangle_set.begin() + 3 * i + 3);
                sol_pt2 += triangle_set[0 + 3 * i] + triangle_set[1 + 3 * i] > triangle_set[2 + 3 * i];
            }
            j = 0;
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