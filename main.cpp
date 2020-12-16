#include "EarleyAlgorithm.h"
#include <cassert>

int main() {
    assert(Tests::test_predict());
    assert(Tests::test_scan());
    assert(Tests::test_complete());

    string word;

    try {
        size_t number_of_rules;
        cin >> number_of_rules;
        vector <string> rules(number_of_rules);
        for (size_t i = 0; i < number_of_rules; i++) {
            cin >> rules[i];
        }

        Grammar grammar(rules);

        cin >> word;
        cout << ((EarleyAlgorithm(grammar).Predict(word)) ? "YES\n" : "NO\n");
    } catch (IncorrectRule& ex) {
        cout << "ERROR";
    }

    return 0;
}
