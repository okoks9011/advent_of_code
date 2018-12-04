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

    unordered_map<int, vector<int>> guards_sleep;
    auto it = records.begin();
    while (it != records.end()) {
        int guard_id = it->guard_id;
        if (!guards_sleep.count(guard_id))
            guards_sleep.emplace(guard_id, vector<int>(60));
        FillSleepVector(&it, &guards_sleep[guard_id], records.end());
    }

    int sleepy_guard = 0;
    int sleepy_minute = 0;
    int most_value = 0;
    for (auto& p : guards_sleep) {
        auto& sleep = p.second;
        auto minute_it = max_element(sleep.begin(), sleep.end());
        if (*minute_it > most_value) {
            most_value = *minute_it;
            sleepy_guard = p.first;
            sleepy_minute = minute_it - sleep.begin();
        }
    }
    cout << sleepy_guard << endl;
    cout << sleepy_minute << ": " << most_value << endl;

    cout << "Answer: " << sleepy_guard * sleepy_minute << endl;
}
