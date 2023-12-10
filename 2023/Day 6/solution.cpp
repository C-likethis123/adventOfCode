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
brute force:
- take in the time.
- iterate through all possible values.
    - for each value, check if i can beat the record
    - increment if i can beat the record
- for all races, multiply by all possible ways

*/
using namespace std;


int main()
{
    string line;
    long long cur_time = 42899189;
    long long distance = 308117012911467;
    long long ways = 0;
    for (long long speed = 1; speed < cur_time; speed++) {
        // compute max distance
        int time_to_move = cur_time - speed;
        int current_distance = time_to_move * speed;
        if (current_distance > distance) {
            ways++;
        }
    }
    
    cout << "ans: " << fixed << ways << '\n';
    return 0;
}
