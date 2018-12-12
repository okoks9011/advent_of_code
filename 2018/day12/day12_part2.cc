#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <sstream>

using namespace std;

deque<bool> ReadPlants(string state) {
    deque<bool> result;
    for (auto& c : state)
        result.emplace_back(c == '#');
    return result;
}

pair<int, bool> ReadPattern(string row) {
    string pattern = row.substr(0, 5);
    int key = 0;
    for (auto& c : pattern) {
        key *= 2;
        if (c == '#')
            key += 1;
    }

    return {key, row[9] == '#'};
}

bool IsGrowing(int k, const deque<bool>& plants, const deque<bool>& patterns) {
    int key = 0;
    for (int i = k-2; i < k+3; ++i) {
        key *= 2;
        if (plants[i])
            key += 1;
    }
    return patterns[key];
}

void PrintPlants(const deque<bool>& plants) {
    for (auto& plant : plants) {
        if (plant)
            cout << "#";
        else
            cout << ".";
    }
    cout << endl;
}

int AddBuffer(deque<bool>* plants_ptr) {
    auto& plants = *plants_ptr;

    int shift = 5;
    for (int j = 0; j < shift; ++j) {
        plants.emplace_back(false);
        plants.emplace_front(false);
    }

    return shift;
}

int RemoveBuffer(deque<bool>* plants_ptr) {
    auto& plants = *plants_ptr;

    int shift = 0;
    auto it = plants.begin();
    while (it != plants.end() && !(*it)) {
        ++it;
        ++shift;
        plants.pop_front();
    }

    auto r_it = plants.rbegin();
    while (r_it != plants.rend() && !(*r_it)) {
        ++r_it;
        plants.pop_back();
    }

    return shift;
}

int CalSum(const deque<bool>& plants, int start_idx) {
    int total = 0;
    for (int i = 0; i < plants.size(); ++i) {
        if (plants[i])
            total += start_idx;
        ++start_idx;
    }
    return total;
}

int main() {
    ifstream file("input.txt");

    string s;
    getline(file, s);
    deque<bool> plants = ReadPlants(s.substr(15));

    getline(file, s);

    deque<bool> patterns(32);
    while (getline(file, s)) {
        auto p = ReadPattern(s);
        patterns[p.first] = p.second;
    }

    int start_idx = 0;
    int gen = 0;
    int last_sum = 0;
    for (; gen < 100; ++gen) {
        last_sum = CalSum(plants, start_idx);
        cout << gen << ", " << start_idx << ", " << last_sum << ": ";
        PrintPlants(plants);

        start_idx -= AddBuffer(&plants);
        deque<bool> next(plants);
        for (int k = 2; k < next.size()-2; ++k)
            next[k] = IsGrowing(k, plants, patterns);
        plants = next;
        start_idx += RemoveBuffer(&plants);
    }

    cout << "Last sum: " << last_sum << endl;
    int cur_sum = CalSum(plants, start_idx);
    cout << gen << ", " << start_idx << ", " << cur_sum << ": ";
    PrintPlants(plants);

    const long long goal = 50000000000;
    cout << "Goal: " << goal << " gen" << endl;

    long long result = cur_sum;
    result += (goal - gen) * (cur_sum - last_sum);
    cout << "Answer: " << result << endl;
}
