#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include "helper.hpp"

void solve_pt1()
{
    std::ifstream file("inputs/day12");
    std::string line;
    std::unordered_map<std::string, int> registry{{"a", 0}, {"b", 0}, {"c", 1}, {"d", 0}, {"1", 1}};
    std::vector<std::string> instructions;
    while (getline(file, line))
        instructions.push_back(line);

    size_t i = 0;
    while (i < instructions.size())
    {
        //std::cout << i << std::endl;
        //std::cout << "a:" << registry["a"] << ", b: " << registry["b"] << ", c:" << registry["c"] << ", d:" << registry["d"] << std::endl;
        auto parts = tokenize(instructions[i], " ");
        if (parts[0] == "cpy")
        {
            try
            {
                registry[parts[2]] = std::stoi(parts[1]);
            }
            catch(...)
            {
                registry[parts[2]] = registry[parts[1]];
            }
            i++;
        } else if (parts[0] == "inc")
        {
            registry[parts[1]]++;
            i++;
        } else if (parts[0] == "dec")
        {
            registry[parts[1]]--;
            i++;
        } else if (parts[0] == "jnz")
        {
            if (registry[parts[1]] != 0)
                i += std::stoi(parts[2]);
            else
                i++;
        }
    }
    std::cout << "a:" << registry["a"] << ", b: " << registry["b"] << ", c:" << registry["c"] << ", d:" << registry["d"] << std::endl;
}



int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

