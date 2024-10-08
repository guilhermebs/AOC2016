#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include "helper.hpp"

void solve_pt1()
{
    std::ifstream file("inputs/day23");
    std::string line;
    std::unordered_map<std::string, int> registry{{"a", 12}, {"b", 0}, {"c", 0}, {"d", 0}, {"0", 0}, {"1", 1}, {"2", 2}, {"80", 80}, {"87", 87}, {"-16", -16}};
    std::vector<std::vector<std::string>> instructions;
    while (getline(file, line))
        instructions.push_back(tokenize(line, " "));

    size_t i = 0;
    size_t niter = 0;
    while (i < instructions.size() && niter < 10000)
    {
        niter++;
        std::cout << "a:" << registry["a"] << ", b: " << registry["b"] << ", c:" << registry["c"] << ", d:" << registry["d"] << std::endl;
        //for (auto &[k, v]: registry) std::cout << k << ": " << v << ", ";
        //std::cout << std::endl;
        auto parts = instructions[i];
        std::cout << i << ": ";
        for (auto &p: parts) std::cout << p << " ";
        std::cout << std::endl;
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
            int jump;
            try
            {
                jump = std::stoi(parts[2]);
            }
            catch(...)
            {
                jump = registry[parts[2]];
            }
            if (registry[parts[1]] != 0)
                i += jump;
            else
                i++;
        } else if (parts[0] == "tgl")
        {
            auto target = registry[parts[1]] + i;
            if (target < 0 || target >= instructions.size()) { i++; continue; }
            if (instructions[target][0] == "inc") instructions[target][0] = "dec";
            else if (instructions[target][0] == "dec" || instructions[target][0] == "tgl") instructions[target][0] = "inc";
            else if (instructions[target][0] == "jnz") instructions[target][0] = "cpy";
            else if (instructions[target][0] == "cpy") instructions[target][0] = "jnz";
            i++;
        }
    }
    for (auto &[k, v]: registry) std::cout << k << ": " << v << ", ";
    std::cout << std::endl;
    // 11 * 12 * 10
    for (auto &parts: instructions)
    {
        for (auto &p: parts) std::cout << p << " ";
        std::cout << std::endl;
    }
}



int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

