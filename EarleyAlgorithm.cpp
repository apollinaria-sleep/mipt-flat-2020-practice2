#include "EarleyAlgorithm.h"


bool operator<(const Situation& left, const Situation& right) {
    if (left.rule == right.rule) {
        if (left.point == right.point) {
            return left.index < right.index;
        }
        return left.point < right.point;
    }
    return left.rule < right.rule;
}


void EarleyAlgorithm::Predict(size_t index) {
    for (const Situation& situation : states_[index]) {
        for (const Rule& rule : grammar_.GetRules()) {
            if (rule.from == situation.rule.to[situation.point]) {
                Situation new_situation {0, index, rule};
                states_[index].insert(new_situation);
            }
        }
    }
}


void EarleyAlgorithm::Complete(size_t index) {
    for (const Situation& situation : states_[index]) {
        if (situation.point == situation.rule.to.size()) {
            for (const Situation& next_situation : states_[situation.index]) {
                if (next_situation.rule.to[next_situation.point] == situation.rule.from) {
                    Situation new_situation {next_situation.point + 1, next_situation.index, next_situation.rule};
                    states_[index].insert(new_situation);
                }
            }
        } else {
            continue;
        }
    }
}


void EarleyAlgorithm::Scan(char symbol, size_t index) {
    for (const Situation& situation : states_[index]) {
        if (situation.rule.to[situation.point] == symbol) {
            Situation new_situation {situation.point + 1, situation.index, situation.rule};
            states_[index + 1].insert(new_situation);
        }
    }
}


EarleyAlgorithm::EarleyAlgorithm(Grammar grammar) {
    grammar_ = move(grammar);
}


bool EarleyAlgorithm::Predict(const string &word) {
    checking_ = word;

    states_.clear();
    states_.resize(checking_.size() + 1);
    Situation new_situation {0, 0, grammar_.GetRules()[0]};
    states_[0].insert(new_situation);

    size_t prev_size;
    do {
        prev_size = states_[0].size();
        Predict(0);
        Complete(0);
    } while (states_[0].size() != prev_size);

    for (size_t i = 0; i < checking_.size(); i++) {
        Scan(checking_[i], i);
        do {
            prev_size = states_[i + 1].size();
            Predict(i + 1);
            Complete(i + 1);
        } while (states_[i + 1].size() != prev_size);
    }

    Situation end {1, 0, grammar_.GetRules()[0]};
    return (states_[checking_.size()].find(end) != states_[checking_.size()].end());
}


EarleyAlgorithm Tests::MakeGrammarToTest() {
    vector <string> Rules;
    Rules.emplace_back("S->S+P");
    Rules.emplace_back("S->P");
    Rules.emplace_back("P->P*T");
    Rules.emplace_back("P->T");
    Rules.emplace_back("T->(S)");
    Rules.emplace_back("T->x");
    Rules.emplace_back("T->y");
    Rules.emplace_back("T->z");
    Grammar grammar(Rules);
    EarleyAlgorithm test (grammar);
    return test;
}


bool Tests::test_predict() {
    EarleyAlgorithm test = MakeGrammarToTest();
    test.states_.resize(1);

    Situation first_situation {2, 0, test.grammar_.GetRules()[3]};
    test.states_[0].insert(first_situation);
    test.Predict(0);
    first_situation.point = 0;
    first_situation.rule = test.grammar_.GetRules()[5];
    bool test_first = (test.states_[0].find(first_situation) != test.states_[0].end());

    Situation second_situation {0, 0, test.grammar_.GetRules()[1]};
    test.states_[0].insert(second_situation);
    test.Predict(0);
    first_situation.rule = test.grammar_.GetRules()[2];
    bool test_second = (test.states_[0].find(first_situation) != test.states_[0].end());

    return test_first && test_second;
}


bool Tests::test_scan() {
    EarleyAlgorithm test = MakeGrammarToTest();
    test.states_.resize(3);

    Situation first_situation {0, 0, test.grammar_.GetRules()[7]};
    test.states_[0].insert(first_situation);
    test.Scan('y', 0);
    first_situation.point++;
    bool test_first = (test.states_[1].find(first_situation) != test.states_[1].end());

    Situation second_situation {2, 1, test.grammar_.GetRules()[5]};
    test.states_[1].insert(second_situation);
    test.Scan(')', 1);
    second_situation.point++;
    bool test_second = (test.states_[2].find(second_situation) != test.states_[2].end());

    return test_first && test_second;
}


bool Tests::test_complete() {
    EarleyAlgorithm test = MakeGrammarToTest();
    test.states_.resize(2);

    Situation situation {1, 0, test.grammar_.GetRules()[5]};
    test.states_[0].insert(situation);
    Situation first_situation {3, 0, test.grammar_.GetRules()[1]};
    test.states_[1].insert(first_situation);
    test.Complete(1);
    situation.point++;
    bool test_ = (test.states_[1].find(situation) != test.states_[1].end());

    return test_;
}


