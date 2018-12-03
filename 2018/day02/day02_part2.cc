#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

using std::fstream;

using std::string;

using std::vector;

int CalDiff(const string& id1, const string& id2) {
    int diff = 0;
    for (int i = 0; i < id1.size(); ++i) {
        if (id1[i] != id2[i])
            ++diff;
    }
    return diff;
}

string RemoveDiff(const string& id1, const string& id2) {
    string result;
    for (int i = 0; i < id1.size(); ++i) {
        if (id1[i] == id2[i])
            result.push_back(id1[i]);
    }
    return result;
}

int main() {
    fstream file("input.txt");

    vector<string> ids;
    string s;
    while (file >> s)
        ids.emplace_back(s);

    for (int i = 0; i < ids.size(); ++i) {
        for (int j = i+1; j < ids.size(); ++j) {
            string& id1 = ids[i];
            string& id2 = ids[j];
            if (CalDiff(id1, id2) == 1) {
                cout << "=== Found ===" << endl;
                cout << id1 << endl;
                cout << id2 << endl;
                cout << "Answer: " << RemoveDiff(id1, id2) << endl;
            }
        }
    }

}
