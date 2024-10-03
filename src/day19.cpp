#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>

static size_t N_ELVES = 3001330;
//static size_t N_ELVES = 5;

std::vector<int>::iterator find_next_elve(std::vector<int> &elves, std::vector<int>::iterator &cur_elve)
{
        auto next_elve = std::find_if(cur_elve+1, elves.end(), [](auto &e) { return e > 0; });
        if(next_elve == elves.end())
            next_elve = std::find_if(elves.begin(), elves.end(), [](auto &e) { return e > 0; });
        return next_elve;
}

void solve_pt1()
{
    std::vector<int> elves(N_ELVES, 1);
    auto cur_elve = elves.begin();
    while (true)
    {
        auto next_elve = find_next_elve(elves, cur_elve);
        if (next_elve == cur_elve)
            break;
        else
        {
            *cur_elve += *next_elve;
            *next_elve = 0;
        }
        cur_elve = find_next_elve(elves, cur_elve);
    }
    std::cout << "Part 1 solution: " << cur_elve - elves.begin() + 1 << std::endl;
}


void solve_pt2(size_t N)
{
    std::vector<int> elves(N);
    std::iota(elves.begin(), elves.end(), 1);
    size_t cur_pos = 0;
    size_t nelves = N;
    while (nelves > 1)
    {
        auto pos_across = (nelves / 2 + cur_pos) % nelves;
        if (nelves % 1000 == 0) std::cout << nelves << std::endl;
        //std::cout << nelves << ": ";
        //for (auto e: elves)
        //{
        //    std::cout << e << " ";
        //}
        //std::cout << std::endl;
        //std::cout << cur_pos << ", " << pos_across << std::endl;
        nelves--;
        for (auto i = pos_across; i < nelves; i++)
            elves[i] = elves[i + 1];
        elves[nelves] = -1;
        if (pos_across < cur_pos) cur_pos--;
        cur_pos = (cur_pos + 1) % nelves;
    }
    std::cout << "Part 2 solution: " << elves[0] << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2(N_ELVES);
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

