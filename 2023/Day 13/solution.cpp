#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cassert>


using namespace std;

/*

Solution computes rolling hashes for each row and column and compares rolling hashes to check for symmetry
To check for symmetry: 
1. iterate through the hashes
2. iterate from middle to the end, comparing along the way
3. if there is a symmetry, return

*/
int find_symmetry(vector<int>& hashes) {
    for (int i = 0; i < hashes.size() - 1; i++) {
        int c = i + 1;
        int step = c < (hashes.size() - c) ? c : (hashes.size() - c);
        bool has_symmetry = true;
        for (int s = 1; s <= step; s++) {
            if (hashes[c - s] != hashes[c+s-1]) {
                has_symmetry = false;
                break;
            }
        }
        if (has_symmetry) {
            return c;
        }
    }
    return -1;
}

int main()
{
    long ans = 0;
    string line;
    ifstream test_case("input.txt");
    vector<int> horizontal_rolling_hashes;
    vector<int> vertical_rolling_hashes;
    if (test_case.is_open()) {
        while (getline(test_case, line)) {
            if (!line.empty()) {
                 int horizontal_hash = 0;
                for (int i = 0; i < line.size(); i++) {
                    int letter = (line[i] == '#');
                    horizontal_hash *= 2;
                    horizontal_hash += letter;

                    // initialises vertical hash
                    if (vertical_rolling_hashes.size() < i + 1) {
                        vertical_rolling_hashes.push_back(letter);
                    } else {
                        vertical_rolling_hashes[i] *= 2;
                        vertical_rolling_hashes[i] += letter;
                    }
                }
                horizontal_rolling_hashes.push_back(horizontal_hash);
            } else {
                // find horizontal palindrome:
                /*
                    for every column, check if rolling hashes match
                    if there is a symmetry found, add to the sum and move on.
                */
                int row = find_symmetry(horizontal_rolling_hashes);
                if (row != -1) {
                    ans += row * 100;
                } else {
                    // find vertical palindrome, using the same method
                    int column = find_symmetry(vertical_rolling_hashes);
                    assert(column != -1);
                    ans += column;
                }
                horizontal_rolling_hashes.clear();
                vertical_rolling_hashes.clear();
            }
        }       
    }
    // computes rolling hash for the last pattern
    int row = find_symmetry(horizontal_rolling_hashes);
    if (row != -1) {
        ans += row * 100;
    } else {
        int column = find_symmetry(vertical_rolling_hashes);
        assert(column != -1);
        ans += column;
    }
    cout << fixed << "ans: " << ans << endl;
    return 0;
}
