#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

void RemoveEntry(char c, map<char, unordered_set<char>>* depend_ptr) {
    auto& depend = *depend_ptr;
    for (auto& p : depend)
        p.second.erase(c);
}

char FindNext(const map<char, unordered_set<char>>& depend) {
    for (auto& p : depend) {
        if (p.second.empty())
            return p.first;
    }
    return -1;
}

int main() {
    ifstream file("input.txt");

    map<char, unordered_set<char>> depend;
    string s;
    while (getline(file, s)) {
        char from = s[5];
        char to = s[36];
        if (!depend.count(to))
            depend[to] = unordered_set<char>();
        if (!depend.count(from))
            depend[from] = unordered_set<char>();
        depend[to].emplace(from);
    }

    for (auto& p : depend) {
        cout << "=====" << endl;
        cout << p.first << endl;
        for (auto& c : p.second)
            cout << c << " ";
        cout << endl;
    }

    vector<char> history;
    while (!depend.empty()) {
        char cur = FindNext(depend);
        RemoveEntry(cur, &depend);
        depend.erase(cur);
        history.emplace_back(cur);
    }

    cout << "Anwser: ";
    for (auto& c : history)
        cout << c;
    cout << endl;
}
