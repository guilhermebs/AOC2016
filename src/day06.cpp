#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

void solve()
{
    std::ifstream file("inputs/day06");
    std::vector<std::string> signal;
    std::string line;
    while (getline(file, line))
        signal.emplace_back(line);
    std::unordered_map<char, int> counts;
    std::string decoded_pt1 = "";
    std::string decoded_pt2 = "";
    auto comp = [](auto &p1, auto &p2) { return p1.second < p2.second; };
    for (size_t i = 0; i < signal[0].size(); i++)
    {
        for (char c = 'a'; c <= 'z'; c++)
            counts.insert_or_assign(c, 0);
        for (size_t j = 0; j < signal.size(); j++)
            counts[signal[j][i]]++;
        decoded_pt1.push_back(
            std::max_element(counts.begin(), counts.end(), comp)->first
        );
        decoded_pt2.push_back(
            std::min_element(counts.begin(), counts.end(), comp)->first
        );
    }
    std::cout << "Part 1 solution: " << decoded_pt1 << std::endl;
    std::cout << "Part 2 solution: " << decoded_pt2 << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}