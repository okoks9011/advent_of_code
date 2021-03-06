#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using std::cout;
using std::endl;

using std::ifstream;

using std::string;
using std::getline;
using std::stoi;
using std::istringstream;

using std::vector;

using std::sort;
using std::max_element;

using std::unordered_map;

using std::pair;

enum RecordType {
    kBeginShift = 0,
    kFall,
    kWake,
};

struct Record {
    int minute = 0;
    int guard_id = 0;
    RecordType type = kBeginShift;
    Record() = default;
    Record(int m, int gid, RecordType t) : minute(m), guard_id(gid), type(t) {}
};

Record ParseRecord(const string& s) {
/* Input examples
[1518-08-25 23:57] Guard #3499 begins shift
[1518-10-09 00:51] falls asleep
[1518-10-04 00:53] wakes up
*/
    int guard_id = 0;
    int minute = stoi(s.substr(15, 2));
    RecordType type = kBeginShift;
    switch (s[19]) {
        case 'G': {
            istringstream iss(s.substr(26));
            iss >> guard_id;
            break;
        }
        case 'f': {
            type = kFall;
            break;
        }
        case 'w': {
            type = kWake;
            break;
        }
        default: {
            cout << "Parse Error" << endl;
        }
    }
    return {minute, guard_id, type};
}

int CalSleep(vector<Record>::iterator* it_ptr, const vector<Record>::iterator& end) {
    auto& it = *it_ptr;

    int fall_minute = 0;
    int sleep = 0;
    do {
        if (it->type == kFall) {
            fall_minute = it->minute;
        } else if (it->type == kWake) {
            sleep += it->minute - fall_minute;
        }
        ++it;
    } while (it != end && it->type != kBeginShift);

    return sleep;
}

void FillSleepVector(vector<Record>::iterator* it_ptr, vector<int>* sleeps_ptr, const vector<Record>::iterator& end) {
    auto& it = *it_ptr;
    auto& sleeps = *sleeps_ptr;

    int fall_minute = 0;
    do {
        if (it->type == kFall) {
            fall_minute = it->minute;
        } else if (it->type ==kWake) {
            int wake_minute = it->minute;
            for (int i = fall_minute; i < wake_minute; ++i)
                ++sleeps[i];
        }
        ++it;
    } while (it != end && it->type != kBeginShift);
}

int main() {
    ifstream file("input.txt");

    vector<string> raws;
    string s;
    while (getline(file, s))
        raws.emplace_back(s);

    sort(raws.begin(), raws.end());
    vector<Record> records(raws.size());
    for (int i = 0; i < raws.size(); ++i)
        records[i] = ParseRecord(raws[i]);

    auto it = records.begin();
    unordered_map<int, int> guards_sleep;
    while (it != records.end()) {
        int cur_guard = it->guard_id;
        guards_sleep[cur_guard] += CalSleep(&it, records.end());
    }

    auto guard_it = max_element(guards_sleep.begin(), guards_sleep.end(),
                                [](const pair<int, int>& p1, const pair<int, int>& p2) {
                                    return p1.second < p2.second;
                                });
    int sleepy_guard = guard_it->first;
    cout << "Sleepy guard: " << sleepy_guard << " minutes: " << guard_it->second << endl;

    vector<int> sleeps(60);
    it = records.begin();
    while (it != records.end()) {
        if (it->guard_id == sleepy_guard) {
            FillSleepVector(&it, &sleeps, records.end());
        } else {
            CalSleep(&it, records.end());
        }
    }

    auto minute_it = max_element(sleeps.begin(), sleeps.end());
    int sleepy_minute = minute_it - sleeps.begin();
    cout << sleepy_minute << ": " << *minute_it << endl;

    cout << "Answer: " << sleepy_guard * sleepy_minute << endl;
}
