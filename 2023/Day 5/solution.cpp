#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

/*
idea:
- read seeds
- read map
- iterate through seeds, copy seeds and create mapping.
- take the new mapping and remap until its done

- issues: for new mapping, i cannot depend on array numbering.


how to do one mapping:
- seed to soil: use a set to represent all numbers. 
- if there is a number that needs to be remapped, remove the number and replace with the remapped number.
    - this would not work if the remapping range overlaps, so i need two copies.
    - a set means all the numbers would need to be copied, which is a waste of space. 
    it would be better to just save the mappings that needs to be remapped.


things to take note of:
- integer overflows
- when changing a type (eg long to long long), take note of all the possible values, data structures that hold these values.
*/
using namespace std;

typedef tuple<long long, long long, long long> Entry;
typedef vector<Entry> Map;

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

vector<long long> get_seeds(ifstream &input) {
    string line;
    vector<string> v;
    getline(input, line);
    line = line.substr(std::string("seeds: ").size());
    split(line, v, " ");

    vector<long long> res;
    for (string num : v) {
        res.push_back(stoll(num));
    }
    return res;
}

Map get_map(ifstream &input) {
    string line;
    getline(input, line); // skip first line
    Map res;
    vector<string> v;
    while (getline(input, line) && !line.empty()) {
        split(line, v, " ");
        res.emplace_back(stol(v[0]), stol(v[1]), stol(v[2]));
        v.clear();
    }
    return res;
}

void transform(vector<long long>& seeds, Map& map) {
    vector<long long> res = seeds;
    for (int i = 0; i < seeds.size(); i++) {
        long long seed = seeds[i];
        for (Entry e : map) {
            long long dest = std::get<0>(e);
            long long src = std::get<1>(e);
            long long len = std::get<2>(e);
            bool in_range = (seed >= src) && (seed < (src + len));
            if (in_range) {
                long long offset = seed - src;
                long long new_seed = dest + offset;
                res[i] = new_seed;
            }
        }
    }
    seeds = res;
}

int main()
{
    long long ans;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        vector<long long> seeds = get_seeds(test_case);
        getline(test_case, line);
        Map seeds_soil_map = get_map(test_case);
        transform(seeds, seeds_soil_map);

        Map soil_fertilizer_map = get_map(test_case);
        transform(seeds, soil_fertilizer_map);

        Map fertilizer_water_map = get_map(test_case);
        transform(seeds, fertilizer_water_map);

        Map water_light_map = get_map(test_case);
        transform(seeds, water_light_map);

        Map light_temp_map = get_map(test_case);
        transform(seeds, light_temp_map);

        Map temp_humidity_map = get_map(test_case);
        transform(seeds, temp_humidity_map);

        Map humidity_location_map = get_map(test_case);
        transform(seeds, humidity_location_map);

        ans = *min_element(seeds.begin(), seeds.end());
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
