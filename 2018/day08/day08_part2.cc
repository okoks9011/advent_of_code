#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int CalValue(vector<int>::iterator* it_ptr) {
    auto& it = *it_ptr;

    int child_cnt = *it++;
    int meta_cnt = *it++;

    int value = 0;
    if (!child_cnt) {
        for (int i = 0; i < meta_cnt; ++i)
            value += *it++;
    } else {
        unordered_map<int, int> child_values;
        for (int i = 1; i <= child_cnt; ++i)
            child_values[i] = CalValue(it_ptr);

        for (int i = 0; i < meta_cnt; ++i)
            value += child_values[*it++];
    }

    return value;
}

int main() {
    ifstream file("input.txt");

    vector<int> seq;
    int n;
    while (file >> n)
        seq.emplace_back(n);

    auto it = seq.begin();
    cout << CalValue(&it) << endl;
}
