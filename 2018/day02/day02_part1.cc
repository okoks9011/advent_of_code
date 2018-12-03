#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;

using std::fstream;

using std::string;

using std::vector;

using std::unordered_map;

int main() {
    fstream file("input.txt");

    vector<string> ids;
    string s;
    while (file >> s)
        ids.emplace_back(s);

    int two = 0;
    int three = 0;
    for (auto& id : ids) {
        unordered_map<char, int> freq;
        for (auto& c : id)
            ++freq[c];

        for (auto& p : freq) {
            if (p.second == 2) {
                ++two;
                break;
            }
        }
        for (auto& p : freq) {
            if (p.second == 3) {
                ++three;
                break;
            }
        }
    }
    cout << two * three << endl;
}
