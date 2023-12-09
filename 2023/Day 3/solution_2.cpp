#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

/*
assumption: input connects at most two numbers together.
solution brief:
- read all numbers and store their coordinates
- for all numbers, check if they are adjacent to a star.
- if adjacent to a star, see if the star connects this number to another number.

mechanics:
- after encountering a number, check if there is an adjacent star.
- if there is an adjacent star, set the number to xxx (mark it as encountered), and check for the presence of another number.
- if there is another number, multiply both and add it to sum.
- return sum.

mark as encountered: when encountering a number, append it to a string, then mark it as encountered.
find another number: once a number is found, backtrack until the start then read the entire number. 
after the number is read, mark it as read.

learnings:
- question assumptions... what is needed to get X to work correctly?

*/

#define N 140
#define IN_BOUNDS(grid) grid >= 0 && grid < N
#define IS_SYMBOL(x)  x == '*'

char matrix[N][N];
int directions[8][2] = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1}
    };

std::pair<int, int> is_near_star(int r, int c) {
    for (auto &direction : directions) {
        int x = r + direction[0];
        int y = c + direction[1];
        if (IN_BOUNDS(x) && IN_BOUNDS(y)) {
            if (IS_SYMBOL(matrix[x][y])){
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

int find_number_from_star(std::pair<int, int> &coords) {
    for (auto &direction : directions) {
        int x = coords.first + direction[0];
        int y = coords.second + direction[1];
        if (IN_BOUNDS(x) && IN_BOUNDS(y)) {
            if (isdigit(matrix[x][y])){
                string num;
                while (IN_BOUNDS(y) && isdigit(matrix[x][y])) {
                    y--;
                }
                y += 1;
                while (IN_BOUNDS(y) && isdigit(matrix[x][y])) {
                    num += matrix[x][y];
                    matrix[x][y] = 'x';
                    y++;
                }
                return stoi(num);
            }
        }
    }
    return -1;
}

int main()
{
    string line;
    double ans;
    
    ifstream test_case("input.txt");
    int r = 0;
    if (test_case.is_open()) {
        while (getline(test_case,line)) {
            for (int c = 0; c < N; c++) {
                matrix[r][c] = line[c];
            }
            r++;
        }

        for (r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (isdigit(matrix[r][c])) {
                    bool is_gear_ratio = false;
                    std::pair<int, int> star_coords;
                    std::string num;
                    int x = c;
                    while (x < N && isdigit(matrix[r][x])) {
                        num += matrix[r][x];
                        matrix[r][x] = 'x';
                        pair<int, int> temp_star_coords = is_near_star(r, x);
                        if (temp_star_coords.first != -1 && temp_star_coords.second != -1) {
                            is_gear_ratio = true;
                            star_coords = temp_star_coords;
                        }
                        x++;
                    }
                    if (is_gear_ratio) {
                        int num_found = find_number_from_star(star_coords);
                        if (num_found != -1) {
                            ans += stoi(num) * num_found;
                        }
                    }
                }
            }
        }
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
