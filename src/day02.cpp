#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>

void solve_pt1()
{
    std::fstream file("inputs/day02");
    std::vector<int> sequence;
    std::string line;
    int number = 5;
    while (getline(file, line))
    {
        for(auto const &c: line)
        {
            switch (c)
            {
            case 'U':
                number = (number < 4)? number: number - 3;
                break;
            case 'D':
                number = (number > 6)? number: number + 3;
                break;
            case 'L':
                number = (((number - 1) % 3) == 0)? number: number - 1;
                break;
            case 'R':
                number = (((number - 3) % 3) == 0)? number: number + 1;
                break;
            default:
                throw std::runtime_error("Invalid char!");
            }
        }
        sequence.push_back(number);
    }
    std::cout << "Part 1 solution: ";
    for (auto &n: sequence)
        std::cout << n;
    std::cout << std::endl;
}

void solve_pt2()
{
    std::fstream file("inputs/day02");
    std::string line;
    char cur_pos = '5';
    const std::unordered_map<std::string, char> mappings{
        {"1U", '1'}, {"1R", '1'}, {"1D", '3'}, {"1L", '1'},
        {"2U", '2'}, {"2R", '3'}, {"2D", '6'}, {"2L", '2'},
        {"3U", '1'}, {"3R", '4'}, {"3D", '7'}, {"3L", '2'},
        {"4U", '4'}, {"4R", '4'}, {"4D", '8'}, {"4L", '3'},
        {"5U", '5'}, {"5R", '6'}, {"5D", '5'}, {"5L", '5'},
        {"6U", '2'}, {"6R", '7'}, {"6D", 'A'}, {"6L", '5'},
        {"7U", '3'}, {"7R", '8'}, {"7D", 'B'}, {"7L", '6'},
        {"8U", '4'}, {"8R", '9'}, {"8D", 'C'}, {"8L", '7'},
        {"9U", '9'}, {"9R", '9'}, {"9D", '9'}, {"9L", '8'},
        {"AU", '6'}, {"AR", 'B'}, {"AD", 'A'}, {"AL", 'A'},
        {"BU", '7'}, {"BR", 'C'}, {"BD", 'D'}, {"BL", 'A'},
        {"CU", '8'}, {"CR", 'C'}, {"CD", 'C'}, {"CL", 'B'},
        {"DU", 'B'}, {"DR", 'D'}, {"DD", 'D'}, {"DL", 'D'},
    };
    std::cout << "Part 2 solution: ";
    while (getline(file, line))
    {
        for(auto const &c: line)
            cur_pos = mappings.at(std::string{cur_pos, c});
        std::cout << cur_pos;
    }
    std::cout << std::endl;
}
 

int main()
{
    auto started = std::chrono::high_resolution_clock::now();
    solve_pt1();
    solve_pt2();
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms\n";

}