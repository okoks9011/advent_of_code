#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

struct Worker {
    int id = 0;
    char task = -1;
    int remain = 0;
};

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

bool IsAllWorkerIdle(const vector<Worker>& workers) {
    return all_of(workers.begin(), workers.end(),
                  [](const Worker& w) {
                      return w.task == -1;
                  });
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
        cout << "[";
        for (auto& c : p.second)
            cout << c << " ";
        cout << "] => " << p.first << endl;
    }

    vector<Worker> workers(5);
    for (int i = 0; i < workers.size(); ++i)
        workers[i].id = i;

    int time = 0;
    do {
        for (auto& worker : workers) {
            if (worker.task != -1)
                continue;

            char cur = FindNext(depend);
            if (cur != -1) {
                worker.task = cur;
                worker.remain = (cur - 4);
                depend.erase(cur);
                cout << "[A] Worker #" << worker.id << ": Task " << worker.task << " assigned at " << time << endl;
            }
        }

        for (auto& worker : workers)
            --worker.remain;

        for (auto& worker : workers) {
            if (worker.task == -1)
                continue;

            if (worker.remain == 0) {
                cout << "[D] Worker #" << worker.id << ": Task " << worker.task << " done at " << time << endl;
                RemoveEntry(worker.task, &depend);
                worker.task = -1;
            }
        }
        ++time;
    } while (!IsAllWorkerIdle(workers) || !depend.empty());

    cout << "Time: " << time << endl;;
}
