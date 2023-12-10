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
problem statement: instead of a list of values, how to make it work for a list of range of values?

some observations:
- we can apply the transformation to a "range" instead of all the values.
- when needed, we need to "split" the range of values.


pair: [start, range]
"intervals needed":
- initial values
- transformations: source to destination values
  - handle the case where only parts of the number ranges are translated, including how to split the pairs etc.

- find minimum value from number ranges

Data structure: list of "number range"
operations:
    - find minimum value
    - update range with transformation
maintain assumptions:
    - sort ranges - easier to replace
    - ranges are non overlapping - overlapping ranges should be merged

Huge question: how to update?
- two things to update: range + start
- full transformations: update "start" from source to destination
- splitting range: 
    when split into two ranges:
    1. find affected region. split into two ranges.
    2. transform affected range.

    when split into 3 ranges:
    1. split into 3 ranges
    2. transform middle range

Avoiding errors:
- modifying the same data structure while iterating through it is not a good sign.
- copy into a new data structure as we're adding to it.


Data structures needed:
- Pair: [start, range]
    - vector<Pair> update(Transformation)
        - return new range, transform if needed
- Transformation: [start, end, range]
- NumberRange
    - vector<Pair>, sorted
    - add(Pair p) op:
        - add a pair to the underlying representation
        - no updates needed: completely overlaps with existing information
        - merge needed: update start/range
        - add range
    - update(NumberRange r, Transformation t)
        - iterate through all pairs in NumberRange
        completely overlap: create a new pair.
        is in middle: split into 3 pairs. transform the middle. return.
        is in half: split into affected and non affected region. transform affected region. return.
        - add to a new data structure, return new data structure

*/
using namespace std;

class Transformation {
    public:
        long long src;
        long long dest;
        long long range;
        Transformation(long long src, long long dest, long long range) : src(src), dest(dest), range(range){};
};

typedef vector<Transformation> Transformations;

class Pair {
    public: 
        long long start;
        long long range;
        long long end;
        Pair(long long start, long long range) : start(start), range(range), end(range + start - 1) {};
        void print(vector<Pair>& ranges) {
            for (Pair& p : ranges) {
                cout << "["<< p.start << ", "<< p.end << "],";
            }
            cout << endl;
        };
        vector<Pair> transform(Transformation& t) {
            long long t_end = t.src + t.range;
            cout << "transform: ";
            vector<Pair> res;
            if (t_end < start || end < t.src) {
                res.emplace_back(*this);
                print(res);
                return {*this};
            }
            // 1. fully overlapping
            if (t.src <= start && t_end >= end) {
                long long offset = start - t.src;
                res.emplace_back(t.dest + offset, range);
                print(res);
                return {
                    Pair(t.dest + offset, range)
                };
            // 2. only front is affected
            } else if (t.src <= start && t_end < end) {
                long long affected_range = t_end - start;
                long long offset = start - t.src;
                res.emplace_back(t.dest + offset, affected_range);
                res.emplace_back(t_end+ 1, end - t_end);
                print(res);
                return {
                    Pair(t.dest + offset, affected_range),
                    Pair(t_end + 1, end - t_end)
                };
            // 3. only back is affected
            } else if (t.src > start && t_end >= end) {
                long long affected_range_1 = t.src - start;
                long long affected_range_2 = end - t.src;
                res.emplace_back(start, affected_range_1);
                res.emplace_back(t.dest, affected_range_2);
                print(res);
                return {
                    Pair(start, affected_range_1),
                    Pair(t.dest, affected_range_2)
                };
            // 4. the middle is affected
            } else {
                long long range_1 = t.src - start;
                long long range_2 = t.range;
                long long range_3 = end - t_end;
                res.emplace_back(start, range_1);
                res.emplace_back(t.dest, range_2);
                res.emplace_back(t_end + 1, range_3);
                print(res);
                return {
                    Pair(start, range_1),
                    Pair(t.dest, range_2),
                    Pair(t_end + 1, range_3)
                };
            }
        };
};

class NumberRange {
    public:
        vector<Pair> ranges;
        void add(Pair &new_pair) {
            vector<Pair> new_ranges;
            for (int i = 0; i < ranges.size(); i++){
                if (ranges[i].end < new_pair.start) {
                    new_ranges.push_back(ranges[i]);
                } else if (new_pair.end < ranges[i].start) {
                    new_ranges.push_back(new_pair);
                    new_ranges.insert(new_ranges.end(), ranges.begin() + i, ranges.end());
                    ranges.swap(new_ranges);
                    return;
                } else {
                    long long new_start = min(new_pair.start, ranges[i].start);
                    long long new_end = max(new_pair.end, ranges[i].end);
                    new_pair = Pair(new_start, new_end - new_start + 1);
                }
            }
            new_ranges.push_back(new_pair);
            ranges.swap(new_ranges);
        };

        void add(vector<Pair> &pairs) {
            for (Pair &p : pairs) {
                add(p);
            }
        };

        NumberRange update(Transformation& t) {
            NumberRange res;
            for (Pair &p : ranges) {
                vector<Pair> new_pairs = p.transform(t);
                res.add(new_pairs);
            }
            return res;
        };

        long long get_min() {
            return ranges[0].start;
        };
        
        void print() {
            for (Pair& p : ranges) {
                cout << "["<< p.start << ", "<< p.end << "],";
            }
            cout << endl;
        };
};

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

NumberRange get_seeds(ifstream &input) {
    string line;
    vector<string> v;
    getline(input, line);
    line = line.substr(std::string("seeds: ").size());
    split(line, v, " ");

    NumberRange res;
    for (int i = 0; i < v.size() - 1; i += 2) {
        Pair new_pair(stoll(v[i]), stoll(v[i+1]));
        res.add(new_pair);
    }
    return res;
}

Transformations get_map(ifstream &input) {
    string line;
    getline(input, line); // skip first line
    cout << line;
    Transformations res;
    vector<string> v;
    while (getline(input, line) && !line.empty()) {
        split(line, v, " ");
        res.emplace_back(stoll(v[1]), stoll(v[0]), stoll(v[2]));
        v.clear();
    }
    return res;
}

void transform(NumberRange& seeds, Transformations& map) {
    for (Transformation& t : map) {
        seeds = seeds.update(t);
    }
    seeds.print();
}

int main()
{
    long long ans;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        NumberRange seeds = get_seeds(test_case);
        getline(test_case, line);
        Transformations seeds_soil_map = get_map(test_case);
        transform(seeds, seeds_soil_map);
        cout << seeds.get_min() <<endl;

        Transformations soil_fertilizer_map = get_map(test_case);
        transform(seeds, soil_fertilizer_map);
        cout << seeds.get_min() <<endl;

        Transformations fertilizer_water_map = get_map(test_case);
        transform(seeds, fertilizer_water_map);
        cout << seeds.get_min() <<endl;

        Transformations water_light_map = get_map(test_case);
        transform(seeds, water_light_map);
        cout << seeds.get_min() <<endl;

        Transformations light_temp_map = get_map(test_case);
        transform(seeds, light_temp_map);
        cout << seeds.get_min() <<endl;

        Transformations temp_humidity_map = get_map(test_case);
        transform(seeds, temp_humidity_map);
        cout << seeds.get_min() <<endl;

        Transformations humidity_location_map = get_map(test_case);
        transform(seeds, humidity_location_map);
        cout << seeds.get_min() <<endl;

        ans = seeds.get_min();
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
