#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

void ClockWise(list<int>::iterator* it_ptr, list<int>& circle) {
    auto& it = *it_ptr;
    ++it;
    if (it == circle.end())
        it = circle.begin();
}

void CounterClockWise(list<int>::iterator* it_ptr, list<int>& circle) {
    auto& it = *it_ptr;
    if (it == circle.begin())
        it = circle.end();
    --it;
}

int RemoveMarble(list<int>::iterator* it_ptr, list<int>& circle) {
    auto& it = *it_ptr;
    it = circle.erase(it);
    if (it == circle.end())
        it = circle.begin();
}

void PrintCircle(int cur_player, const list<int>& circle, const list<int>::iterator& cur_it) {
    cout << "[" << cur_player << "] ";
    for (auto it = circle.begin(); it != circle.end(); ++it) {
        if (it == cur_it)
            cout << "(" << *it << ")";
        else
            cout << *it;
        cout << " ";
    }
    cout << endl;
}

int main() {
    const int players = 424;
    const int last_marble = 71482;

    list<int> circle{0};
    vector<int> scores(players);
    int cur_player = 0;
    int cur_marble = 1;
    auto cur_it = circle.begin();
    while (cur_marble <= last_marble) {
        if (cur_marble % 23) {
            ClockWise(&cur_it, circle);
            ClockWise(&cur_it, circle);
            cur_it = circle.emplace(cur_it, cur_marble);
        } else {
            scores[cur_player] += cur_marble;
            for (int i = 0; i < 7; ++i)
                CounterClockWise(&cur_it, circle);
            scores[cur_player] += *cur_it;
            RemoveMarble(&cur_it, circle);
        }

        ++cur_marble;
        ++cur_player;
        cur_player %= players;
    }

    cout << "== Total scores ==" << endl;
    for (int i = 0; i < scores.size(); ++i)
        cout << i << ": " << scores[i] << endl;
    cout << endl;
    auto it = max_element(scores.begin(), scores.end());
    cout << "Answer: " << *it << endl;
}
