#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Star {
    int px = 0;
    int py = 0;
    int vx = 0;
    int vy = 0;
    Star() = default;
    Star(int pos_x, int pos_y, int vel_x, int vel_y) : px(pos_x), py(pos_y), vx(vel_x), vy(vel_y) {}
};

Star ParseStar(const string& s) {
    istringstream pos(s.substr(10, 14));
    string tmp;
    int px, py;
    pos >> px >> tmp >> py;

    istringstream vel(s.substr(36, 6));
    int vx, vy;
    vel >> vx >> tmp >> vy;

    return {px, py, vx, vy};
}

void Running(vector<Star>* stars_ptr, bool forward) {
    auto& stars = *stars_ptr;

    for (auto& star : stars) {
        if (forward) {
            star.px += star.vx;
            star.py += star.vy;
        } else {
            star.px -= star.vx;
            star.py -= star.vy;
        }
    }
}

int DiffMinMaxY(const vector<Star>& stars) {
    auto cmp_py = [](const Star& s1, const Star& s2) {
                      return s1.py < s2.py;
                  };
    auto min_it = min_element(stars.begin(), stars.end(), cmp_py);
    auto max_it = max_element(stars.begin(), stars.end(), cmp_py);
    return max_it->py - min_it->py;
}

ostream& operator<<(ostream& os, Star s) {
    os << "(" << s.px << ", " << s.py << ") : ";
    os << s.vx << ", " << s.vy;
    return os;
}

void PrintStars(const vector<Star>& stars) {
    vector<Star> moved(stars);
    auto cmp_px = [](const Star& s1, const Star& s2) {
                      return s1.px < s2.px;
                  };
    auto cmp_py = [](const Star& s1, const Star& s2) {
                      return s1.py < s2.py;
                  };

    auto min_x = min_element(stars.begin(), stars.end(), cmp_px);
    auto min_y = min_element(stars.begin(), stars.end(), cmp_py);
    for (auto& s : moved) {
        s.px -= min_x->px;
        s.py -= min_y->py;
    }

    auto max_x = max_element(moved.begin(), moved.end(), cmp_px);
    auto max_y = max_element(moved.begin(), moved.end(), cmp_py);
    cout << "max x: " << max_x->px << ", max y: " << max_y->py << endl;

    vector<vector<char>> plain(max_y->py+1, vector<char>(max_x->px+1, ' '));
    for (auto& s : moved)
        plain[s.py][s.px] = '#';

    for (auto& row : plain) {
        for (auto& dot : row)
            cout << dot;
        cout << endl;
    }
}

int main() {
    ifstream file("input.txt");

    vector<Star> stars;
    string s;
    while (getline(file, s))
        stars.emplace_back(ParseStar(s));

    cout << "Start Y Diff: " << DiffMinMaxY(stars) << endl;

    int before = numeric_limits<int>::max();
    int current = DiffMinMaxY(stars);
    int time = 0;
    while (before > current) {
        Running(&stars, true);
        ++time;
        before = current;
        current = DiffMinMaxY(stars);
    }
    Running(&stars, false);
    --time;

    cout << "Time: " << time << endl;
    cout << "Y Diff: " << DiffMinMaxY(stars) << endl;

    PrintStars(stars);
}
