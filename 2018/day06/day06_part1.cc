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
    ifstream file("input_sol.txt");

    string s;
    vector<pair<int, int>> dots;
    while (getline(file, s)) {
        istringstream iss(s);
        int x, y;
        char tmp;
        iss >> x >> tmp >> y;
        dots.emplace_back(x, y);
        cout << "(" << x << ", " << y << ")" << endl;
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

    vector<vector<int>> plain(plain_size, vector<int>(plain_size, -1));
    unordered_map<int, int> areas;
    for (int i = 0; i < plain_size; ++i) {
        for (int j = 0; j < plain_size; ++j) {
            plain[i][j] = ClosestDot({i, j}, dots);
            ++areas[plain[i][j]];
            cout << plain[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < plain_size; ++i) {
        areas.erase(plain[i][0]);
        areas.erase(plain[i][plain_size-1]);
        areas.erase(plain[0][i]);
        areas.erase(plain[plain_size-1][i]);
    }

    int max_dot = -1;
    int max_v = numeric_limits<int>::min();
    for (auto& p : areas) {
        cout << p.first << " " << p.second << endl;
        if (p.second > max_v) {
            max_dot = p.first;
            max_v = p.second;
        }
    }

    cout << "Area size: " << areas.size() << endl;
    cout << max_dot << " " << max_v << endl;
}
