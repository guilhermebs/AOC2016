#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>

static size_t WIDTH = 50;
static size_t HEIGHT = 6;

void solve_pt1()
{
    std::ifstream file("inputs/day08");
    std::string line;
    static std::regex pattern_rect("rect (\\d+)x(\\d+)");
    static std::regex pattern_row("rotate row y=(\\d+) by (\\d+)");
    static std::regex pattern_col("rotate column x=(\\d+) by (\\d+)");
    std::smatch match;
    std::string display(WIDTH * HEIGHT, '.');
    while (getline(file, line))
    {
        auto new_state = display;
        if (std::regex_match(line, match, pattern_rect))
        {
            size_t rect_w = std::stoi(match[1]);
            size_t rect_h = std::stoi(match[2]);
            for (size_t y = 0; y < rect_h; y++)
            {
                for (size_t x = 0; x < rect_w; x++)
                    new_state[x + y * WIDTH] = '#';
            }
        } else if (std::regex_match(line, match, pattern_row))
        {
            auto y = std::stoi(match[1]);
            auto shift = std::stoi(match[2]);
            for (size_t x = 0; x < WIDTH; x++)
                new_state[(x + shift)%WIDTH + y * WIDTH] = display[x + y * WIDTH];
            
        } else if (std::regex_match(line, match, pattern_col))
        {
            auto x = std::stoi(match[1]);
            auto shift = std::stoi(match[2]);
            for (size_t y = 0; y < HEIGHT; y++)
                new_state[x + ((y + shift)%HEIGHT) * WIDTH] = display[x + y * WIDTH];
        } else {
            std::cout << "Error!" << std::endl;
        }
        display = new_state;
    }
    std::cout << "Part 1 solution: " << std::count(display.begin(), display.end(), 1)  << std::endl;
    for (size_t y = 0; y < HEIGHT; y++)
    {
        std::cout << display.substr(y * WIDTH, WIDTH) << std::endl;
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
