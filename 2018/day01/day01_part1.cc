#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

using std::fstream;

int main() {
    fstream file("input.txt");

    int sum = 0;
    int a;
    while (file >> a) {
        sum += a;
    }
    cout << sum << endl;
}
