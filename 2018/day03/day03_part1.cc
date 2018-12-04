#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;

using std::fstream;

using std::string;
using std::getline;

using std::vector;

using std::istringstream;

using std::max;

struct Claim {
    int left_margin = 0;
    int top_margin = 0;
    int width = 0;
    int height = 0;
    Claim(int l, int t, int w, int h) : left_margin(l), top_margin(t), width(w), height(h) {}
};

Claim ReadClaim(string s) {
    istringstream iss(s);
    string tmp;
    char tmp_c;
    int left_margin, right_margin;
    // claim example: #1 @ 45,64: 22x22
    iss >> tmp >> tmp >> left_margin >> tmp_c >> right_margin >> tmp;
    int width, height;
    iss >> width >> tmp_c >> height;
    return {left_margin, right_margin, width, height};
}

void ColorFabric(vector<vector<int>>* fabric_ptr, Claim claim) {
    auto& fabric = *fabric_ptr;
    for (int i = claim.top_margin; i < claim.top_margin+claim.height; ++i) {
        for (int j = claim.left_margin; j < claim.left_margin+claim.width; ++j) {
            ++fabric[i][j];
        }
    }
}

int main() {
    fstream file("input.txt");

    vector<Claim> claims;
    string s;
    while (getline(file, s))
        claims.emplace_back(ReadClaim(s));

    int fabric_width = 0;
    int fabric_height = 0;
    for (auto& claim : claims) {
        fabric_width = max(fabric_width, claim.left_margin+claim.width);
        fabric_height = max(fabric_height, claim.top_margin+claim.height);
    }

    vector<vector<int>> fabric(fabric_height+1, vector<int>(fabric_width+1, 0));
    for (auto& claim : claims) {
        ColorFabric(&fabric, claim);
    }

    int count = 0;
    for (int i = 0; i < fabric.size(); ++i) {
        for (int j = 0; j < fabric[i].size(); ++j) {
            if (fabric[i][j] > 1)
                ++count;
        }
    }
    cout << count << endl;
}
