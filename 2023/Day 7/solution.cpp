#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>

/*

1. list of cards, and bid
2. rank the cards (put in a priority queue? what's the equivalent in c++?)

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

unordered_map<char, int> strength = {
    {'A',14 },
    {'K',13 },
    {'Q',12 },
    {'J',11 },
    {'T',10 },
    {'9',9 },
    {'8',8 },
    {'7',7},
    {'6',6},
    {'5',5 },
    {'4',4 },
    {'3',3},
    {'2',2}
};

class Card {
    public:
        string card;
        Card(string card) : card(card) {};
        friend bool operator<(const Card& l, const Card& r) {
            for (int i = 0; i < 5; i++) {
                int l_strength = strength[l.card[i]];
                int r_strength = strength[r.card[i]];
                if (l_strength < r_strength) {
                    return true;
                } else if (r_strength < l_strength) {
                    return false;
                }
            }
            // it's a tie, return false
            return false;
        };
};

int FIVE_OF_A_KIND = 6;
int FOUR_OF_A_KIND = 5;
int FULL_HOUSE = 4;
int THREE_OF_A_KIND = 3;
int TWO_PAIR = 2;
int ONE_PAIR = 1;
int HIGH_CARD = 0;
class Hand {
    public:
        Card card;
        long bid;
        Hand(string s, int bid) : card(s), bid(bid) {};
        int get_move() const {
            unordered_map<char, int> map;
            for (char c : card.card) {
                if (map.find(c) != map.end()) {
                    map[c] += 1;
                } else {
                    map[c] = 1;
                }
            }
            if (map.size() == 1) {
                return FIVE_OF_A_KIND;
            } else if (map.size() == 2) {
                int max_size = 0;
                for (auto &x : map) {
                    max_size = max(x.second, max_size);
                }
                if (max_size == 4) {
                    return FOUR_OF_A_KIND;
                } else {
                    return FULL_HOUSE;
                }
            } else if (map.size() == 3) {
                int max_size = 0;
                for (auto &x : map) {
                    max_size = max(x.second, max_size);
                }
                if (max_size == 3) {
                    return THREE_OF_A_KIND;
                } else {
                    return TWO_PAIR;
                }
            } else if (map.size() == 4) {
                return ONE_PAIR;
            } else {
                return HIGH_CARD;
            }
        };
        friend bool operator<(const Hand& l, const Hand& r) {
            int l_move = l.get_move();
            int r_move = r.get_move();
            if (l_move < r_move) {
                return true;
            } else if (l_move > r_move) {
                return false;
            } else {
                return l.card < r.card;
            }
        };
};

int main()
{
    long long ans = 0;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        priority_queue<Hand> hands;
        vector<string> v;
        while (getline(test_case, line)){
            split(line, v, " ");
            hands.emplace(v[0], stol(v[1]));
            v.clear();
        }
        
        long rank = hands.size();
        for (; !hands.empty(); hands.pop()) {
            Hand h = hands.top();
            ans += rank * h.bid;
            rank -= 1;
        }

    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
