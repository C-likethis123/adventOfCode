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
solution brief:
- read all numbers and store their coordinates
- for all numbers, check if they are adjacent a symbol.

time complexity: O(nm)

Learnings:
- must specify dimension for multi-dimension arrays (second dimension onwards)
- initialise array like this: char matrix[x][y] NOT char[][] matrix;
*/

#define IN_BOUNDS(grid) grid >= 0 && grid < 140
#define IS_SYMBOL(x) !(isalpha(x) || isdigit(x)) && x != '.'

int N = 140;
char matrix[140][140];


bool check_part_num(int r, int c) {
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
    for (auto &direction : directions) {
        if (IN_BOUNDS(r + direction[0]) && IN_BOUNDS(c + direction[1])) {
            if (IS_SYMBOL(matrix[r + direction[0]][c+direction[1]])){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    string line;
    double ans;
    
    ifstream test_case("input.txt");
    int r = 0;
    if (test_case.is_open()) {
        while (getline (test_case,line)) {
            for (int c = 0; c < 140; c++) {
                matrix[r][c] = line[c];
            }
            r++;
        }

        for (r = 0; r < 140; r++) {
            for (int c = 0; c < 140; c++) {
                if (isdigit(matrix[r][c])) {
                    std::string num;
                    bool is_part_num = false;
                    while (c < 140 && isdigit(matrix[r][c])) {
                        num += matrix[r][c];
                        if (check_part_num(r, c)) {
                            is_part_num = true;
                        }
                        c++;
                    }
                    if (is_part_num) {
                        ans += stoi(num);
                    }
                }
            }
        }
    }
    cout << "ans: " << ans << '\n';
    return 0;
}
