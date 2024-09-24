#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <regex>

std::string checksum(const std::string &name)
{
    std::vector<int> counts(26, 0);
    for (char i = 0; i < 27; i++)
        counts[i] = std::count(name.begin(), name.end(), 'a' + i);

    std::vector<char> order(26); 
    std::iota(order.begin(), order.end(), 0);
    std::stable_sort(order.begin(), order.end(), [&counts](char i1, char i2) {return counts[i1] > counts[i2]; });
    std::string result("");
    for (size_t i = 0; i < 5; i++)
        result.push_back('a' + order[i]);
    return result;
}


std::string decript(const std::string &name, const int id)
{
    std::string result;// = name;
    std::transform(name.begin(), name.end(), std::back_inserter(result), [&id](char c) {
        if (c == '-')
            return ' ';
        return static_cast<char>((((int)(c - 'a') + id) % ('z' - 'a' + 1)) + 'a');
    });
    return result;
}

void solve()
{
    std::ifstream file("inputs/day04");
    std::string line;
    static std::regex pattern("(.+)-(\\d+)\\[(\\w+)\\]");
    std::smatch match;
    int sol_pt1 = 0;
    while (getline(file, line))
    {
        if (std::regex_match(line, match, pattern))
        {
            std::string name = match[1];
            int id = stoi(match[2]);
            std::string check = match[3];
            if (check == checksum(name))
                sol_pt1 += id;
            //std::cout << decript(name, id) << std::endl;
            if (decript(name, id) == "northpole object storage")
                std::cout << "Part 2 solution: " << id << std::endl;
        }
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}