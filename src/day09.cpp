#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>

void solve_pt1()
{
    std::ifstream file("inputs/day09");
    std::string line;
    getline(file, line);
    //line = "A(2x2)BCD(2x2)EFG";
    //line = "(6x1)(1x3)A";
    //line = "X(8x2)(3x3)ABCY";
    static std::regex rex("\\((\\d+)x(\\d+)\\)");
    std::smatch sm;
    std::string expanded;
    while (std::regex_search(line, sm, rex))
    {
        int nchars = std::stoi(sm[1]);
        int nreps = std::stoi(sm[2]);
        expanded.append(sm.prefix());
        auto seq2copy = line.substr(sm.position() + sm.length(), nchars);
        for (int i = 0; i < nreps; i++)
            expanded.append(seq2copy);
        line = line.substr(sm.position() + sm.length() + nchars);
    }
    expanded.append(line);
    std::cout << "Part 1 solution: " << expanded.size() << std::endl;
    
}

long long unsigned int count_nested(const std::string &str)
{
    static std::regex rex("\\((\\d+)x(\\d+)\\)");
    std::smatch sm;
    long long unsigned int result = 0;
    if (std::regex_search(str, sm, rex))
    {
        result += sm.position();
        int nchars = std::stoi(sm[1]);
        int nreps = std::stoi(sm[2]);
        auto to_expand = str.substr(sm.position() + sm.length(), nchars);
        result += count_nested(to_expand) * nreps;
        result += count_nested(str.substr(sm.position() + sm.length() + nchars));
    } else {
        result = str.size();
    }
    return result;
}

void solve_pt2()
{
    std::ifstream file("inputs/day09");
    std::string line;
    getline(file, line);
    //line = "A(2x2)BCD(2x2)EFG";
    //line = "(6x1)(1x3)A";
    //line = "X(8x2)(3x3)ABCY";
    //line = "(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN";
    std::cout << "Part 2 solution: " << count_nested(line) << std::endl;
}
 

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}


