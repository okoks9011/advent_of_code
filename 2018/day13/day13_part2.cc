#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <deque>

using namespace std;

enum Direction {
    kUp = 0,
    kRight,
    kDown,
    kLeft,
};

struct Cart {
    int id = 0;
    int y = 0;
    int x = 0;
    Direction d = kUp;
    int d_cnt = 0;

    Cart() = default;
    Cart(int i) : id(i) {}
    Cart(int i, int px, int py, Direction direc) : id(i), y(py), x(px), d(direc) {}

    bool operator<(const Cart& other) const {
        if (y == other.y)
            return x < other.x;
        return y < other.y;
    }
    bool operator==(const Cart& other) const {
        return id == other.id;
    }
};

bool IsCart(char c) {
    return (c == '^' || c == '>' || c == 'v' || c == '<');
}

Direction GetDirection(char c) {
    if (c == '^')
        return kUp;
    else if (c == '>')
        return kRight;
    else if (c == 'v')
        return kDown;
    else if (c == '<')
        return kLeft;

    return kUp;
}

char GetCart(Direction d) {
    if (d == kUp)
        return '^';
    else if (d == kRight)
        return '>';
    else if (d == kDown)
        return 'v';
    else if (d == kLeft)
        return '<';

    return ' ';
}

ostream& operator<<(ostream& os, const Cart& c) {
    os << "Cart [" << c.id << "] (" << c.x << ", " << c.y << "), d: " << GetCart(c.d);
    os << " (" << c.d << ")";
    return os;
}

char FindRail(const vector<string>& map, const int x, const int y) {
    unordered_map<char, deque<bool>> connected;
    // According to the Direction structure
    // up, right, down, left
    connected['-'] = deque<bool>{false, true, false, true};
    connected['|'] = deque<bool>{true, false, true, false};
    connected['+'] = deque<bool>{true, true, true, true};
    connected['/'] = deque<bool>{true, true, true, true};
    connected['\\'] = deque<bool>{true, true, true, true};
    connected[' '] = deque<bool>{false, false, false, false};

    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
    if (y > 0)
        up = connected[map[y-1][x]][kDown];
    if (x < map[0].size()-1)
        right = connected[map[y][x+1]][kLeft];
    if (y < map.size()-1)
        down = connected[map[y+1][x]][kUp];
    if (x > 0)
        left = connected[map[y][x-1]][kRight];

    vector<char> rails(16, ' ');
    //   0
    // 3 x 1
    //   2
    // TFTF, 1010 (10) => '|'
    rails[10] = '|';
    // FTFT, 0101 (5) => '-'
    rails[5] = '-';
    // TTTT, 1111 (15) => '+'
    rails[15] = '+';
    // TTFF, 1100 (12) => '/'
    // FFTT, 0011 (3) => '/'
    rails[12] = '/';
    rails[3] = '/';
    // TFFT, 1001 (9) => '\\'
    // FTTF, 0110 (6) => '\\'
    rails[9] = '\\';
    rails[6] = '\\';

    int index = (1 << 3) * up;
    index += (1 << 2) * right;
    index += (1 << 1) * down;
    index += left;

    return rails[index];
}

set<Cart> ExtractCart(vector<string>* map_ptr) {
    auto& map = *map_ptr;

    set<Cart> carts;
    int id_cnt = 0;
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[0].size(); ++x) {
            auto& c = map[y][x];
            if (IsCart(c)){
                auto cart = Cart(id_cnt++, x, y, GetDirection(c));
                cout << cart;
                carts.emplace(cart);

                c = FindRail(map, x, y);
                cout << " => " << c << endl;
            }
        }
    }
    return carts;
}

void PrintMap(const vector<string>& map, const set<Cart>& carts, bool with_carts) {
    vector<string> paint(map);
    for (auto r_it = carts.rbegin(); r_it != carts.rend(); ++r_it) {
        auto& cart = *r_it;
        auto& row = paint[cart.y];
        string colored = "\033[31m";
        if (with_carts)
            colored += GetCart(cart.d);
        else
            colored += paint[cart.y][cart.x];
        colored += "\033[0m";
        row.replace(cart.x, 1, colored);
    }

    cout << "\033c";
    for (int i = 0; i < paint.size(); ++i)
        cout << paint[i] << endl;
}

Cart MoveCart(const Cart cart, char rail) {
    auto new_cart = Cart(cart);

    vector<Direction> turn_left(4);
    turn_left[kUp] = kLeft;
    turn_left[kRight] = kUp;
    turn_left[kDown] = kRight;
    turn_left[kLeft] = kDown;

    vector<Direction> turn_right(4);
    turn_right[kUp] = kRight;
    turn_right[kRight] = kDown;
    turn_right[kDown] = kLeft;
    turn_right[kLeft] = kUp;

    if (rail == '\\') {
        if (new_cart.d == kUp || new_cart.d == kDown)
            new_cart.d = turn_left[new_cart.d];
        else if (new_cart.d == kRight || new_cart.d == kLeft)
            new_cart.d = turn_right[new_cart.d];
    } else if (rail == '/') {
        if (new_cart.d == kUp || new_cart.d == kDown)
            new_cart.d = turn_right[new_cart.d];
        else if (new_cart.d == kRight || new_cart.d == kLeft)
            new_cart.d = turn_left[new_cart.d];
    } else if (rail == '+') {
        if (new_cart.d_cnt == 0)
            new_cart.d = turn_left[new_cart.d];
        else if (new_cart.d_cnt == 2)
            new_cart.d = turn_right[new_cart.d];
        new_cart.d_cnt = (new_cart.d_cnt + 1) % 3;
    }

    if (new_cart.d == kUp)
        new_cart.y -= 1;
    else if (new_cart.d == kRight)
        new_cart.x += 1;
    else if (new_cart.d == kDown)
        new_cart.y += 1;
    else if (new_cart.d == kLeft)
        new_cart.x -= 1;

    return new_cart;
}

Cart CollideCart(const Cart& cart, const set<Cart>& carts) {
    for (auto& cart_i : carts) {
        if (cart.x == cart_i.x && cart.y == cart_i.y)
            return cart_i;
    }
    return Cart(-1);
}

int PlayTickRemain(vector<string>* map_ptr, set<Cart>* carts_ptr) {
    auto& map = *map_ptr;
    auto& carts = *carts_ptr;

    set<Cart> iter_carts(carts);
    set<Cart> crashed;
    for (auto& cart : iter_carts) {
        if (crashed.count(cart))
            continue;
        carts.erase(cart);
        auto new_cart = MoveCart(cart, map[cart.y][cart.x]);

        auto collide_cart = CollideCart(new_cart, carts);
        if (collide_cart.id != -1) {
            cout << "Collide occur! => (" << new_cart.x << "," << new_cart.y << ")";
            cout << " : " << new_cart.id << " and " << collide_cart.id << endl;
            crashed.emplace(collide_cart);
            carts.erase(collide_cart);
        } else {
            carts.emplace(new_cart);
        }
    }

    return carts.size();
}

int main() {
    ifstream file("input.txt");

    vector<string> map;
    string s;
    while (getline(file, s))
        map.emplace_back(s);

    int y_size = map.size();
    int x_size = map[0].size();
    cout << "X size: " << x_size << " Y size: " << y_size << endl;

    auto carts = ExtractCart(&map);
    PrintMap(map, carts, false);
    PrintMap(map, carts, true);

    int remain = carts.size();
    do {
        remain = PlayTickRemain(&map, &carts);
        // PrintMap(map, carts, true);
    } while (remain > 1);

    auto last = *carts.begin();
    cout << "Anser: " << last.x << "," << last.y << endl;
}
