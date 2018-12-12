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

int GridSumAcc(int px, int py, int size, const vector<vector<int>>& accs) {
    int ix = px - 1;
    int iy = py - 1;
    int ox = ix + size;
    int oy = iy + size;

    return accs[ox][oy] - accs[ox][iy] - accs[ix][oy] + accs[ix][iy];
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

    vector<vector<int>> accs(grid_size+1, vector<int>(grid_size+1, 0));
    for (int y = 1; y <= grid_size; ++y) {
        int row_acc = 0;
        for (int x = 1; x <= grid_size; ++x) {
            row_acc += powers[x][y];
            accs[x][y] = row_acc + accs[x][y-1];
        }
    }

    int max_sum = numeric_limits<int>::min();
    int max_x = 0;
    int max_y = 0;
    int max_s = 0;
    for (int s = 1; s <= grid_size; ++s) {
        cout << "\r" << "calculate size " << s << flush;
        for (int y = 1; y <= grid_size-s+1; ++y) {
            for (int x = 1; x <= grid_size-s+1; ++x) {
                int cur_sum = GridSumAcc(x, y, s, accs);
                if (cur_sum > max_sum) {
                    max_sum = cur_sum;
                    max_x = x;
                    max_y = y;
                    max_s = s;
                }
            }
        }
    }
    cout << endl;

    cout << "(x, y, size): " << max_x << "," << max_y << "," << max_s << endl;
    cout << "max powers: " << max_sum << endl;
}
