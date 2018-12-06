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

int ClosestDot(const pair<int, int>& p, const vector<pair<int, int>>& dots) {
    vector<int> d(dots.size());
    for (int i = 0; i < dots.size(); ++i)
        d[i] = Distance(p, dots[i]);

    auto it = min_element(d.begin(), d.end());
    if (count(d.begin(), d.end(), *it) != 1)
        return -1;
    else
        return it - d.begin();
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

    unordered_map<int, int> areas;
    for (int i = 0; i < plain_size; ++i) {
        for (int j = 0; j < plain_size; ++j) {
            int dot_idx = ClosestDot({i, j}, dots);
            ++areas[dot_idx];
        }
    }

    for (int i = 0; i < plain_size; ++i) {
        areas.erase(ClosestDot({i, 0}, dots));
        areas.erase(ClosestDot({i, plain_size-1}, dots));
        areas.erase(ClosestDot({0, i}, dots));
        areas.erase(ClosestDot({plain_size-1, i}, dots));
    }

    auto it_max_dot = max_element(areas.begin(), areas.end(),
                                  [](const pair<int, int>& p1, const pair<int, int>& p2) {
                                      return p1.second < p2.second;
                                  });
    cout << "Area count: " << areas.size() << endl;
    cout << it_max_dot->first << " " << it_max_dot->second << endl;
}
