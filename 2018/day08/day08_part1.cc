#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int SumMeta(vector<int>::iterator* it_ptr) {
    auto& it = *it_ptr;

    int child_cnt = *it++;
    int meta_cnt = *it++;

    int result = 0;
    for (int i = 0; i < child_cnt; ++i)
        result += SumMeta(it_ptr);

    for (int i = 0; i < meta_cnt; ++i)
        result += *it++;

    return result;
}

int main() {
    ifstream file("input.txt");

    vector<int> seq;
    int n;
    while (file >> n)
        seq.emplace_back(n);

    auto it = seq.begin();
    cout << SumMeta(&it) << endl;
}
