#include <chrono>
#include <iostream>
#include <vector>

void solve_pt1()
{
    std::string row(".^^^^^.^^^..^^^^^...^.^..^^^.^^....^.^...^^^...^^^^..^...^...^^.^.^.......^..^^...^.^.^^..^^^^^...^.");
    //std::string row(".^^.^.^^^^");
    static size_t size_x = row.length();
    size_t count = std::count(row.begin(), row.end(), '.');
    for (int y=1; y < 400000; y++)
    {
        //std::cout << row << std::endl;
        std::string next_row = row;
        for (size_t x = 0; x < size_x; x++)
        {
            bool left = (x > 0 && row[x - 1] == '^');
            bool centre = (row[x] == '^');
            bool right = (x < size_x - 1 && row[x + 1] == '^');
            char c = (
                (left && centre && !right) | (!left && centre && right) |
                (left && !centre && !right) | (!left && !centre && right))? '^' : '.';
            next_row[x] = c;
        }
        row = next_row;
        count += std::count(row.begin(), row.end(), '.');
    }
    std::cout << "Solution: " << count << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    //solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

