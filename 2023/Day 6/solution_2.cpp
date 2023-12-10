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
    long long cur_time = //add input;
    long long distance = // add input;
    long long ways = 0;
    for (long long speed = 1; speed < cur_time; speed++) {
        // compute max distance
        long long time_to_move = cur_time - speed;
        long long current_distance = time_to_move * speed;
        if (current_distance > distance) {
            ways++;
        }
    }
    
    ofstream debug("ans.txt");
    debug << fixed << ways;
    cout << "ans: " << fixed << ways << '\n';
    return 0;
}
