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

/**

*/

unordered_map<string,string> digit_map = {
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

void split(string s, std::vector<std::string>& v, string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        v.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
}

int get_game_id(string line) {
    std::vector<std::string> v;
    split(line, v, " ");
    int id = stoi(v[1]);
    return id;
}

void split_cube_subsets(string line, vector<string> &v) {
    vector<string> temp;
    split(line, temp, ":");
    string second_part = temp[1];
    second_part.erase(0, 1);
    
    split(second_part, v, "; ");
}

void cube_numbers(string line, unordered_map<string, int> &m){
    vector<string> temp;
    split(line, temp, ", ");
    for (auto &s : temp) {
        vector<string> temp2;
        split(s, temp2, " ");
        m[temp2[1]] = stoi(temp2[0]);
    }
}

int main()
{
    string line;
    double sum;
    
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        while ( getline (test_case,line) ){
            int game_id = get_game_id(line);
            // split subset of cubes
            vector<string> subsets;
            split_cube_subsets(line, subsets);

            // get cube numbers
            bool possible = true;
            int red_cubes = 0;
            int blue_cubes = 0;
            int green_cubes = 0;
            for (auto &subset : subsets) {
                unordered_map<string, int> cubes;
                cube_numbers(subset, cubes);
                if (cubes["red"] > red_cubes) {
                    red_cubes = cubes["red"];
                }
                if (cubes["blue"] > blue_cubes) {
                    blue_cubes = cubes["blue"];
                }
                if (cubes["green"] > green_cubes) {
                    green_cubes = cubes["green"];
                }
            }

            // compute the powers
            double power = red_cubes * blue_cubes * green_cubes;
            sum += power;
        }
    }
    cout << "sum: "<< sum << '\n';
    return 0;
}
