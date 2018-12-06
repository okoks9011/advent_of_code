#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_map>

using namespace std;

int Distance(const pair<int, int>& p1, const pair<int, int>& p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int TotalDistance(const pair<int, int>& p, const vector<pair<int, int>>& dots) {
    int result = 0;
    for (auto& dot : dots)
        result += Distance(p, dot);
    return result;
}

int main() {
    ifstream file("input.txt");

    string s;
    vector<pair<int, int>> dots;
    while (getline(file, s)) {
        istringstream iss(s);
        int x, y;
        char tmp;
        iss >> x >> tmp >> y;
        dots.emplace_back(x, y);
    }

    auto it_max_x = max_element(dots.begin(), dots.end(),
                                [](const pair<int, int>& p1, const pair<int, int>& p2) {
                                    return p1.first < p2.first;
                                });
    cout << "x max: " << it_max_x->first << endl;
    auto it_max_y = max_element(dots.begin(), dots.end(),
                                [](const pair<int, int>& p1, const pair<int, int>& p2) {
                                    return p1.second < p2.second;
                                });
    cout << "y max: " << it_max_y->second << endl;

    const int plain_size = max(it_max_x->first, it_max_y->second) + 10;
    cout << "plain_size: " << plain_size << endl;

    const int distance_limit = 10000;
    int safe = 0;
    for (int i = 0; i < plain_size; ++i) {
        for (int j = 0; j < plain_size; ++j) {
            if (TotalDistance({i, j}, dots) < distance_limit)
                ++safe;
        }
    }
    cout << "Safe: " << safe << endl;
}
