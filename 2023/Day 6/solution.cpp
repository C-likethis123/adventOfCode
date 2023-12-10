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
    long long ans = 1;
    string line;
    int times[] = {42, 89, 91, 89};
    int distances[] = {308, 1170, 1291, 1467};
    for (int i = 0; i < 4; i++) {
        int cur_time = times[i];
        int distance = distances[i];
        int ways = 0;
        for (int speed = 1; speed < cur_time; speed++) {
            // compute max distance
            int time_to_move = cur_time - speed;
            int current_distance = time_to_move * speed;
            if (current_distance > distance) {
                ways++;
            }
        }
        ans *= ways;
    }
    
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
