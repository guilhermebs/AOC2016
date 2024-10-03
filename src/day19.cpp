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
    std::vector<int> elves_pos(N);
    std::iota(elves_pos.begin(), elves_pos.end(), 0);
    auto cur_elve = elves_pos.begin();
    size_t nelves = N;
    while (nelves > 1)
    {
        auto pos_across = (nelves / 2 + *cur_elve) % nelves;
        auto elve_across = std::find(elves_pos.begin(), elves_pos.end(), pos_across);
        //std::cout << nelves << std::endl;
        //std::cout << nelves << ": ";
        //for (auto e: elves_pos)
        //{
        //    std::cout << e << " ";
        //}
        //std::cout << std::endl;
        //std::cout << *cur_elve << ", " << pos_across << std::endl;
        //std::cout << cur_elve - elves_pos.begin() << ", " << elve_across - elves_pos.begin() << std::endl;
        *elve_across = -1;
        for (auto e = elve_across; e < elves_pos.end(); e++)
            (*e)--;
        nelves--;
        if (*cur_elve == nelves - 1)
        {
            cur_elve = std::find(elves_pos.begin(), elves_pos.end(), 0);
        } else
        {
            cur_elve = std::find(cur_elve, elves_pos.end(), *cur_elve + 1);
        }
    }
    std::cout << "Part 2 solution: " << cur_elve - elves_pos.begin() + 1 << std::endl;
}


int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2(5);
    solve_pt2(50);
    solve_pt2(500);
    solve_pt2(5000);
    solve_pt2(50000);
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}

