#include <iostream>
#include <vector>

using namespace std;

void PrintRecipes(const vector<int>& recipes, const int e1, const int e2) {
    for (int i = 0; i < recipes.size(); ++i) {
        if (i == e1) {
            cout << "(" << recipes[i] << ")";
        } else if (i == e2) {
            cout << "[" << recipes[i] << "]";
        } else {
            cout << " " << recipes[i] << " ";
        }
    }
    cout << endl;
}

bool EndsWith(const vector<int>& recipes, const vector<int>& target) {
    if (recipes.size() < target.size())
        return false;

    int diff = recipes.size() - target.size();
    for (int i = 0; i < target.size(); ++i) {
        if (recipes[diff+i] != target[i])
            return false;
    }

    return true;
}

int main() {
    vector<int> recipes{3, 7};
    int e1 = 0;
    int e2 = 1;

    PrintRecipes(recipes, e1, e2);

    vector<int> target{4, 4, 0, 2, 3, 1};
    while (true) {
        int next = recipes[e1] + recipes[e2];
        if (next / 10) {
            recipes.emplace_back(next / 10);
            if (EndsWith(recipes, target))
                break;
        }
        recipes.emplace_back(next % 10);
        if (EndsWith(recipes, target))
            break;

        e1 = (e1 + recipes[e1] + 1) % recipes.size();
        e2 = (e2 + recipes[e2] + 1) % recipes.size();
        // PrintRecipes(recipes, e1, e2);
    }

    cout << "Found! " << recipes.size() - target.size() << endl;
}
