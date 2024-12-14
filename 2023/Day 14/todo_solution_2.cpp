#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>
#include <climits>
#include <bitset>

/*
problem extension:
- move rocks in different directions
- increase number of iterations

observations: some rocks do not move after a few cycles.

*/
using namespace std;

#define L 100

char matrix[L][L];


/**
keep a pointer to the last "O" field
keep the current pointer.

as we iterate with the current pointer, swap O with current pointer.

pointer: the first '.' that i can move this to.
*/
void move_all_rocks() {
    for (int col = 0; col < L; col++) {
        int ptr = 0;
        int i = 0;
        while (i < L) {
            if (matrix[i][col] == 'O') {
                matrix[ptr][col] = matrix[i][col];
                ptr += 1;
            }
            bool no_reset_needed = true;
            while (matrix[i][col] == '#') {
                no_reset_needed = false;
                for (int j = ptr; j < i; j++) {
                    matrix[j][col] = '.';
                }
                i++;
                ptr = i;
            }
            if (no_reset_needed) {
                i++;
            }
        }
        for (int i = ptr; i < L; i++) {
            matrix[i][col] = '.';
        }
    }
}

/*
type safety: use long
assumptions:
- matrix length and breath is L
- load is one-indexed
*/

long compute_load() {
    long res = 0;
    for (int r = 0; r < L; r++) {
        int load = L - r;
        int num_rocks = 0;
        for (int c = 0; c < L; c++) {
            if (matrix[r][c] == 'O') {
                num_rocks++;
            }
        }
        res += load * num_rocks;
    }
    return res;
}

int main()
{
    long ans = 0;
    string line;
    ifstream test_case("input.txt");
    // ofstream debug("output.txt");
    
    if (test_case.is_open()) {
        for (int r = 0; r < L; r++) {
            getline(test_case, line);
            for (int c = 0; c < L; c++) {
                matrix[r][c] = line[c];
            }
        }

        move_all_rocks();
        // for (int r = 0; r < L; r++) {
        //     for (int c = 0; c < L; c++) {
        //         debug << matrix[r][c];
        //     }
        //     debug<< endl;
        // }
        long ans = compute_load();
        cout << fixed << ans << endl;
    }
    return 0;
}
