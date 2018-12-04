#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

using std::ifstream;

using std::string;
using std::getline;
using std::stoi;
using std::istringstream;

using std::vector;

using std::sort;

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
}
