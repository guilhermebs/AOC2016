#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>

std::string rotate_str(const std::string &string, int nsteps)
{
    std::string result = string;
    for (int i = 0; i < (int) string.length(); i++)
    {
        auto idx = i + nsteps;
        idx = (idx < 0)? 2*string.length() + idx: idx;
        result[i] = string[idx % string.length()];
    }
    return result;
}

void solve_pt1()
{
    std::fstream file("inputs/day21");
    std::string line;
    static std::regex swap_pos("swap position (\\d+) with position (\\d+)");
    static std::regex swap_letter("swap letter (\\w) with letter (\\w)");
    static std::regex rotate_steps("rotate (\\w+) (\\d+) steps?");
    static std::regex rotate_pos("rotate based on position of letter (\\w+)");
    static std::regex reverse_pos("reverse positions (\\d+) through (\\d+)");
    static std::regex move_pos("move position (\\d+) to position (\\d+)");
    std::smatch sm;
    std::string string("abcdefgh");
    //std::string string("abcde");
    while (getline(file, line))
    {
        if (std::regex_match(line, sm, swap_pos))
        {
            auto pos1 = std::stoi(sm[1]);
            auto pos2 = std::stoi(sm[2]);
            std::swap(string[pos1], string[pos2]);

        } else if (std::regex_match(line, sm, swap_letter))
        {
            auto l1 = sm[1].str()[0];
            auto l2 = sm[2].str()[0];
            std::replace(string.begin(), string.end(), l1, '.');
            std::replace(string.begin(), string.end(), l2, l1);
            std::replace(string.begin(), string.end(), '.', l2);
        } else if (std::regex_match(line, sm, rotate_steps))
        {
            auto sign = (sm[1] == "left")? 1 : -1;
            auto nsteps = sign * std::stoi(sm[2]);
            string = rotate_str(string, nsteps);
        } else if (std::regex_match(line, sm, rotate_pos))
        {
            auto l = sm[1].str()[0];
            auto pos = std::find(string.begin(), string.end(), l) - string.begin();
            int nsteps = -(pos + 1 + (pos >= 4));
            string = rotate_str(string, nsteps);
        } else if (std::regex_match(line, sm, reverse_pos))
        {
            auto pos1 = std::stoi(sm[1]);
            auto pos2 = std::stoi(sm[2]);
            std::reverse(string.begin()+pos1, string.begin()+pos2+1);
        } else if (std::regex_match(line, sm, move_pos))
        {
            auto pos1 = std::stoi(sm[1]);
            auto pos2 = std::stoi(sm[2]);
            auto c = string[pos1];
            string.erase(pos1, 1);
            string.insert(pos2, 1,  c);
        } else
        {
            std::cout << line << std::endl;
        } 
        std::cout << line << std::endl;
        std::cout << string << std::endl;
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