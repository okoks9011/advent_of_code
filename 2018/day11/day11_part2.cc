#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int CalPower(int x, int y, int serial) {
    int rack_id = x + 10;
    long long power = y * rack_id;
    power += serial;
    power *= rack_id;
    power = (power / 100) % 10;
    power -= 5;

    return power;
}

int GridSum(int px, int py, int size, const vector<vector<int>>& powers) {
    int sum = 0;
    for (int x = px; x < px+size; ++x) {
        for (int y = py; y < py+size; ++y) {
            sum += powers[x][y];
        }
    }
    return sum;
}

int ShiftX(int px, int py, int size, int acc, const vector<vector<int>>& powers) {
    if (px+size >= powers.size())
        return 0;
    for (int y = py; y < py+size; ++y) {
        acc -= powers[px][y];
        acc += powers[px+size][y];
    }
    return acc;
}

int main() {
    const int serial = 7989;
    const int grid_size = 300;

    vector<vector<int>> powers(grid_size+1, vector<int>(grid_size+1, 0));
    for (int x = 1; x <= grid_size; ++x) {
        for (int y = 1; y <= grid_size; ++y) {
            powers[x][y] = CalPower(x, y, serial);
        }
    }

    int max_sum = numeric_limits<int>::min();
    int max_x = 0;
    int max_y = 0;
    int max_s = 0;
    for (int s = 1; s <= grid_size; ++s) {
        cout << "\r" << "calculate size " << s << flush;
        for (int y = 1; y <= grid_size-s+1; ++y) {
            int cur_sum = GridSum(1, y, s, powers);
            for (int x = 1; x <= grid_size-s+1; ++x) {
                if (cur_sum > max_sum) {
                    max_sum = cur_sum;
                    max_x = x;
                    max_y = y;
                    max_s = s;
                }
                cur_sum = ShiftX(x, y, s, cur_sum, powers);
            }
        }
    }
    cout << endl;

    cout << "(x, y, size): " << max_x << "," << max_y << "," << max_s << endl;
    cout << "max powers: " << max_sum << endl;
}
