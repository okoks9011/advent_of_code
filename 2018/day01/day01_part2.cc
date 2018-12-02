#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using std::cout;
using std::endl;

using std::fstream;

using std::vector;

using std::unordered_set;

int main() {
    fstream file("input.txt");

    vector<int> v;
    int a;
    while (file >> a) {
        v.emplace_back(a);
    }

    unordered_set<int> history;
    int i = 0;
    int sum = 0;
    while (history.count(sum) == 0) {
        history.emplace(sum);
        sum += v[i];
        i = (i+1) % v.size();
    }
    cout << sum << endl;
}
