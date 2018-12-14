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

int main() {
    vector<int> recipes{3, 7};
    int e1 = 0;
    int e2 = 1;

    PrintRecipes(recipes, e1, e2);

    const int target = 440231;
    while (recipes.size() < target+10) {
        int next = recipes[e1] + recipes[e2];
        if (next / 10)
            recipes.emplace_back(next / 10);
        recipes.emplace_back(next % 10);

        e1 = (e1 + recipes[e1] + 1) % recipes.size();
        e2 = (e2 + recipes[e2] + 1) % recipes.size();
        // PrintRecipes(recipes, e1, e2);
    }

    cout << "Target: " << target << " Answer: ";
    for (int i = target; i < target+10; ++i)
        cout << recipes[i];
    cout << endl;
}
