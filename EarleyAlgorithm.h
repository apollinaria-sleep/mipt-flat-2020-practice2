#include "Grammar.h"


struct Situation {
    size_t point = 0;
    size_t index = 0;
    Rule rule;
};


class EarleyAlgorithm {
public:
    EarleyAlgorithm() = default;
    explicit EarleyAlgorithm(Grammar grammar);
    bool Predict(const string& word);
    friend class Tests;
private:
    void Predict(size_t index);
    void Scan(char symbol, size_t index);
    void Complete(size_t index);
    Grammar grammar_;
    string checking_;
    vector <set <Situation>> states_;
};


class Tests {
public:
    static bool test_predict();
    static bool test_scan();
    static bool test_complete();
private:
    static EarleyAlgorithm MakeGrammarToTest();
};
