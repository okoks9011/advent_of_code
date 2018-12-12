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

int GridSum(int px, int py, const vector<vector<int>>& powers) {
    int sum = 0;
    for (int x = px; x < px+3; ++x) {
        for (int y = py; y < py+3; ++y) {
            sum += powers[x][y];
        }
    }
    return sum;
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
    for (int x = 1; x <= grid_size-3+1; ++x) {
        for (int y = 1; y <= grid_size-3+1; ++y) {
            int cur_sum = GridSum(x, y, powers);
            if (cur_sum > max_sum) {
                max_sum = cur_sum;
                max_x = x;
                max_y = y;
            }
        }
    }

    cout << "coordinate: " << max_x << "," << max_y << endl;
    cout << "max powers: " << max_sum;
}
