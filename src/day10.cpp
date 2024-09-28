#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <regex>

struct Bot
{
    std::string low_target;
    std::string high_target;
    std::vector<int> chips;
};


void solve_pt1()
{
    std::ifstream file("inputs/day10");
    std::string line;
    std::unordered_map<std::string, Bot> bots;
    static std::regex rules("(.+) gives low to (.+) and high to (.+)");
    static std::regex init_state("value (\\d+) goes to (.+)");
    std::smatch sm;
    while (getline(file, line))
    {
        if (std::regex_match(line, sm, rules))
        {
            auto bot = sm[1];
            auto low_target = sm[2];
            auto high_target = sm[3];
            bots[bot].low_target = low_target;
            bots[bot].high_target = high_target;
        } else if (std::regex_match(line, sm, init_state))
        {
            auto value = std::stoi(sm[1]);
            auto bot = sm[2];
            bots[bot].chips.push_back(value);
        } else
        {
            std::cout << "Error!" << std::endl;
        }
    }
    while (true)
    {
        auto bot_2_chips = std::find_if(bots.begin(), bots.end(), [](const auto &b) { return b.second.chips.size() == 2 && !b.first.starts_with("output"); });
        if (bot_2_chips == bots.end()) break;
        auto low = *std::min_element(bot_2_chips->second.chips.begin(), bot_2_chips->second.chips.end());
        auto high = *std::max_element(bot_2_chips->second.chips.begin(), bot_2_chips->second.chips.end());
        if (low == 17 && high == 61)
        {
            std::cout << "Part 1 solution: " << bot_2_chips->first << std::endl;
        }
        bots[bot_2_chips->second.low_target].chips.push_back(low);
        bots[bot_2_chips->second.high_target].chips.push_back(high);
        bot_2_chips->second.chips.clear();
    }
    int sol_pt2 = 1;
    for (auto output: {"output 0", "output 1", "output 2"})
    {
        for (int c: bots[output].chips)
            sol_pt2 *= c;
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

