#include <chrono>
#include <iostream>
#include <set>
#include <array>
#include <vector>
#include <deque>
#include <algorithm>

bool floor_is_ok(const std::set<int> &objects)
{
    auto has_generators = std::any_of(objects.begin(), objects.end(), [](const auto &o) { return o < 0; });
    if (!has_generators) return true;
    for (const auto &o: objects)
    {
        if (o > 0  && !objects.contains(-o))
            return false;
    }
    return true;
};

struct State
{
    std::array<std::set<int>, 4> objects;
    int cur_floor;
    bool is_final() const
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (objects[i].size() > 0)
                return false;
        }
        return true;
    }
    std::string to_string() const
    {
        std::string result;
        for (int i = 3; i >= 0; i--)
        {
            result.append("F" + std::to_string(i+1) + " ");
            for (const auto &o: objects[i])
                result.append(std::to_string(o) + ", ");
            if (i == cur_floor) result.append("*");
            result.append("\n");
        }
        return result;
    }

    std::vector<State> children() const
    {
        std::vector<State> result;
        for (auto oi = objects[cur_floor].begin(); oi != objects[cur_floor].end(); oi++)
        {
            for (auto oj = oi; oj != objects[cur_floor].end() ; oj++)
            {
                auto floor = objects[cur_floor];
                floor.erase(*oi);
                floor.erase(*oj);
                //check if removing the two object from the current floor will destroy anything
                if (!floor_is_ok(floor))
                    continue;
                // check if we can move them down
                if (cur_floor > 0)
                {
                    auto floor_below = objects[cur_floor - 1];
                    floor_below.insert(*oi);
                    floor_below.insert(*oj);
                    if(floor_is_ok(floor_below))
                    {
                        auto new_objects = objects;
                        new_objects[cur_floor] = floor;
                        new_objects[cur_floor - 1] = floor_below;
                        result.push_back(State{new_objects, cur_floor-1});
                    }
                }
                // check if we can move them up
                if (cur_floor < 3)
                {
                    auto floor_above = objects[cur_floor + 1];
                    floor_above.insert(*oi);
                    floor_above.insert(*oj);
                    if(floor_is_ok(floor_above))
                    {
                        auto new_objects = objects;
                        new_objects[cur_floor] = floor;
                        new_objects[cur_floor + 1] = floor_above;
                        result.push_back(State{new_objects, cur_floor+1});
                    }
                }
            }
        }
        return result;
    }
};


int search(const State &init_state)
{
    std::deque<std::pair<State, int>> queue{{init_state, 0}};
    std::set<std::string> seen;
    while (queue.size() > 0)
    {
        const auto [state, n] = queue.front();
        //std::cout << n << std::endl;
        //std::cout << state.to_string() << std::endl;
        queue.pop_front();
        if (state.is_final())
            return n;
        for (const auto &c: state.children())
        {
            if (!seen.contains(c.to_string()))
            {
                queue.push_back({c, n+1});
                seen.insert(c.to_string());
            }
        }
    }
    return -1;
 
}

void solve_pt1()
{
    State init_state{
        {std::set<int>{1, -1,  2, -2}, {-3, 4, -4, 5, -5}, {3}, {}},
        0
    };
    std::cout << "Part 1 solution: " << search(init_state) << std::endl;
   
}

void solve_pt2()
{
    State init_state{
        {std::set<int>{1, -1,  2, -2, 6, -6, 7, -7}, {-3, 4, -4, 5, -5}, {3}, {}},
        0
    };
    std::cout << "Part 2 solution: " << search(init_state) << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    //solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}
