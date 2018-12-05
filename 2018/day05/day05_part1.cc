#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using std::cout;
using std::endl;

using std::ifstream;

using std::vector;

using std::abs;

bool Reacted(char c1, char c2) {
    return abs(c1 - c2) == ('a' - 'A');
}

int main() {
    ifstream file("input.txt");
    char c;
    vector<char> stack;
    while (file >> c) {
        if (!stack.empty() && Reacted(stack.back(), c)) {
            stack.pop_back();
        } else {
            stack.emplace_back(c);
        }
    }

    cout << stack.size() << endl;
}
