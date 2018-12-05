#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <limits>
#include <algorithm>

using std::cout;
using std::endl;

using std::ifstream;

using std::vector;

using std::abs;

using std::string;

using std::numeric_limits;

using std::min;
using std::remove;

bool Reacted(char c1, char c2) {
    return abs(c1 - c2) == ('a' - 'A');
}

int ReactedLength(string s) {
    vector<int> stack;
    for (auto& c : s) {
        if (!stack.empty() && Reacted(stack.back(), c))
            stack.pop_back();
        else
            stack.emplace_back(c);
    }
    return stack.size();
}

int main() {
    ifstream file("input.txt");

    string s;
    getline(file, s);

    int min_length = numeric_limits<int>::max();
    char diff = 'a' - 'A';
    for (char c = 'A'; c <= 'Z'; ++c) {
        string cur(s);
        auto it_end = remove(cur.begin(), cur.end(), c);
        it_end = remove(cur.begin(), it_end, c+diff);
        cur.erase(it_end, cur.end());

        int length = ReactedLength(cur);
        cout << c << ": " << length << endl;
        min_length = min(min_length, length);
    }

    cout << "min_length: " << min_length << endl;
}
