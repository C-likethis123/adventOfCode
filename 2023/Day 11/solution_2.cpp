#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>
#include <climits>
#include <bitset>

/*

extension:
- swap the increments in the previous solution.
- note: if i double the amount of space, the increment I add is 1 (off by 1)

*/
using namespace std;

void split(string s, std::vector<std::string>& v, string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) {
           v.push_back(token); 
        }
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
}

#define L 140
#define INCREMENT 1000000

int main()
{
    long ans = 0;
    string line;
    char letters[L][L];
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        vector<pair<int, int>> galaxies;
        unordered_map<int, int> x_map;
        unordered_map<int, int> y_map;
        int increment = 0;
        for (int r = 0; getline(test_case, line); r++){
            bool is_double_line = true;
            for (int c = 0; c < line.size(); c++) {
                letters[r][c] = line[c];
                if (line[c] == '#') {
                    galaxies.emplace_back(r, c);
                    x_map[r] = r+increment;
                    is_double_line = false;
                }
            }
            if (is_double_line) {
                increment += INCREMENT - 1;
            }
        }
        test_case.close();

        // adjust columns
        increment = 0;
        for (int c = 0; c < L; c++) {
            bool is_double_line = true;
            for (int r = 0; r < L; r++) {
                if (letters[r][c] == '#') {
                    y_map[c] = c+increment;
                    is_double_line = false;
                }
            }
            if (is_double_line) {
                increment += INCREMENT - 1;
            }
        }

        for (int i = 0; i < galaxies.size() - 1; i++) {
            int f_x = x_map[galaxies[i].first];
            int f_y = y_map[galaxies[i].second];
            cout << i << " is " << f_x << ", " << f_y << endl;
            for (int j = i + 1; j < galaxies.size(); j++) {
                int s_x = x_map[galaxies[j].first];
                int s_y = y_map[galaxies[j].second];
                // cout << j << " is " << s_x << ", " << s_y << endl;
                ans += abs(f_x - s_x) + abs(f_y - s_y);
            }
        }
    } 
    cout << ans << endl;
    return 0;
}
