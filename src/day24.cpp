#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>

const int N_LOC = 8;
const int SIZE_X = 181;

struct State
{
    std::bitset<N_LOC> visited;
    size_t cur_pos;
    size_t nsteps;

    bool operator==(const State &other) const
    {
        return (visited == other.visited && cur_pos == other.cur_pos && nsteps == other.nsteps);
    }

    bool operator<(const State &other) const
    {
        return (nsteps > other.nsteps);
    }

    inline bool is_final() const
    {
        return visited.all();
    }
    
    std::vector<State> descendents(const std::vector<int> &distances) const
    {
        std::vector<State> result;
        for (size_t n=0; n < N_LOC; n++)
        {
            if (!visited[n])
            {
                auto new_visited = visited;
                new_visited.flip(n);
                result.push_back(
                    State{new_visited, n, nsteps + distances[cur_pos + N_LOC * n]}
                );
            }
        }
        return result;
    }

    std::vector<State> descendents_pt2(const std::vector<int> &distances) const
    {
        std::vector<State> result;
        for (size_t n=0; n < N_LOC; n++)
        {
            if (!visited[n])
            {
                auto new_visited = visited;
                new_visited.flip(n);
                if (new_visited.all() && cur_pos != 0) new_visited.flip(0);
                result.push_back(
                    State{new_visited, n, nsteps + distances[cur_pos + N_LOC * n]}
                );
            }
        }
        return result;
    }
};

template <>
struct std::hash<State>
{
    std::size_t operator()(const State &s) const
    {
        return hash<size_t>()(s.visited.to_ulong()) ^ 
               (hash<size_t>()(s.cur_pos) << 2) ^ 
               (hash<size_t>()(s.nsteps) << 4);
    }
};


void solve_pt1()
{
    std::ifstream file("inputs/day24");
    std::string line;
    std::vector<char> map;
    std::unordered_map<int, size_t> locations;

    size_t i = 0;
    while (getline(file, line))
    {
        for (auto &c : line)
        {
            if (c >= '0' && c <= '9')
                locations[c - '0'] = i;
            map.push_back(c);
            i++;
        }
    }
    std::vector<int> distances(N_LOC * N_LOC, 0);
    for (auto &[l1, i1]: locations)
    {
        for ( auto &[l2, i2]: locations)
        {
            if (l1 == l2) continue;
            if (distances[l1 + l2 * N_LOC] != 0) continue;
            std::unordered_set<size_t> visited{i1};
            std::deque<std::pair<size_t, size_t>> queue{{i1, 0}};
            while (queue.size() > 0)
            {
                auto [i, nsteps] = queue.front();
                queue.pop_front();
                if (i == i2)
                {
                    distances[l1 + l2 * N_LOC] = nsteps;
                    distances[l2 + l1 * N_LOC] = nsteps;
                    break;
                }
                for (auto n: {i - 1, i + 1, i - SIZE_X, i + SIZE_X})
                {
                    if (map[n] != '#' && !visited.contains(n))
                    {
                        visited.insert(n);
                        queue.push_back({n, nsteps+1});
                    }
                }
            }
        }
    }
    
    // use a bitset to keep state
    std::priority_queue<State> queue;
    State init_state{1, 0, 0};
    queue.push(init_state);
    std::unordered_set<State> seen{init_state};
    for (; !queue.empty(); queue.pop())
    {
        const auto &s = queue.top();
        if (s.is_final())
        {
            std::cout << "Part 1 solution: " << s.nsteps << std::endl;
            break;
        }
        for (const auto &sd : s.descendents_pt2(distances))
        {
            if (!seen.contains(sd))    
            {
                seen.insert(sd);
                queue.push(sd);
            }
        }
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
