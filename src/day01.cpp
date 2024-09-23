#include "helper.hpp"
#include <chrono>
#include <string>
#include <unordered_set>
#include <fstream>

struct Pos
{
    int x;
    int y;
    Pos(int x, int y): x(x), y(y) {};
    inline bool operator== (const Pos &other) const
    {
        return ((x == other.x) && (y == other.y));
    }

    Pos take_step(int dir, int step) const
    {
        switch (dir)
        {
        case 0:
            return Pos(x+step, y);
        case 1:
            return Pos(x, y+step);
        case 2:
            return Pos(x-step, y);
        case 3:
            return Pos(x, y-step);
        default:
            throw ("Invalid direction!");
        }
    }
};

template <>
struct std::hash<Pos>
{
  std::size_t operator()(const Pos& p) const
  {
    using std::size_t;
    using std::hash;
    using std::string;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return ((hash<int>()(p.x)
             ^ (hash<int>()(p.y) << 1)) >> 1);
  }
};

void solve()
{
    std::ifstream file("inputs/day01");
    std::string token;
    Pos pos(0, 0);
    std::unordered_set<Pos> visited;
    int sol_pt2 = -1;
    int dir = 0;
    while (getline(file, token, ' '))
    {
        dir += (token[0] == 'R') ? 1 : -1;
        dir = (dir < 0) ? 3 : dir % 4;
        int step = stoi(token.substr(1, token.size() - 2));
        for (int i = 0; i < step; i++)
        {
            visited.insert(pos);
            pos = pos.take_step(dir, 1);
            if (sol_pt2 == -1 && visited.contains(pos))
                sol_pt2 = abs(pos.x) + abs(pos.y);

        }
    }
    std::cout << "Part 1 solution: " << abs(pos.x) + abs(pos.y) << std::endl;
    std::cout << "Part 2 solution: " << sol_pt2 << std::endl;
}

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}