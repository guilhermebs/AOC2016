#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_set>
#include <deque>



void solve()
{
    std::fstream file("inputs/day22");
    std::string line;
    const size_t SIZE_Y = 31;
    const size_t SIZE_X = 32;
    getline(file, line);
    getline(file, line);
    static std::regex re("/dev/grid/node-x(\\d+)-y(\\d+)\\s+\\d+T\\s+(\\d+)T\\s+(\\d+)");
    std::smatch sm;
    std::vector<std::pair<int, int>> nodes;
    while (getline(file, line))
    {
        if (std::regex_search(line, sm, re))
        {
            nodes.push_back({std::stoi(sm[3]), std::stoi(sm[4])});
        } else
        {
            std::cout << line << std::endl;
        }
    }
    int sol_pt1 = 0;
    int empty_pos = -1;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        for (size_t j = 0; j < nodes.size(); j++)
        {
            if ((i != j) && (nodes[i].first > 0) && (nodes[j].second >= nodes[i].first))
            {
                sol_pt1++;
                if (empty_pos != -1 && empty_pos != (int) j)
                    std::cout << "More than 1 empty pos!" << std::endl;
                else
                    empty_pos = j;
            }
        }
    }
    std::cout << "Part 1 solution: " << sol_pt1 << std::endl;
    std::bitset<SIZE_X * SIZE_Y> unmovable;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].first > nodes[empty_pos].second)
            unmovable.flip(i);
    }
    size_t goal_pos = (SIZE_X - 1) * SIZE_Y;
    std::unordered_set<size_t> seen{goal_pos + empty_pos * SIZE_X * SIZE_Y};
    std::deque<std::tuple<size_t, size_t, size_t>> queue{{0, goal_pos, empty_pos}};
    std::vector<size_t> neighbours;
    neighbours.reserve(4);
    while (true)
    {
        const auto &[nsteps, gp, ep] = queue.front();
        queue.pop_front();
        if (gp == 0)
        {
            std::cout << "Part 2 solution: " << nsteps << std::endl;
            break;
        }
        auto ex = ep / SIZE_Y;
        if (ex > 0) neighbours.push_back(ep - SIZE_Y);
        if (ex < SIZE_X - 1) neighbours.push_back(ep + SIZE_Y);
        auto ey = ep % SIZE_Y;
        if (ey > 0) neighbours.push_back(ep - 1);
        if (ey < SIZE_Y - 1) neighbours.push_back(ep + 1);
        for (auto en: neighbours)
        {
            if (unmovable[en]) continue;
            auto gn = (gp == en)? ep : gp;
            auto h = gn + en * SIZE_X * SIZE_Y;
            if (!seen.contains(h))
            {
                queue.push_back({nsteps + 1, gn, en});
                seen.insert(h);
            } 
        }
        neighbours.clear();
        
    }
    
}

 
int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}