#include "Grammar.h"


bool Rule::operator==(const Rule& another) const {
    return from == another.from && to == another.to;
}


bool Rule::operator<(const Rule& another) const {
    if (from == another.from) {
        return to < another.to;
    }
    return from < another.from;
}


bool Grammar::IsRuleCorrect(const string& rule) {
    string to = rule.substr(3, rule.size());

    if (!isupper(rule[0])) {
        throw IncorrectRule();
    }

    if (rule.size() < 3 || rule.find("->") != 1) {
        throw IncorrectRule();
    }

    return true;
}


void Grammar::AddRule(const string &rule) {
    non_terminals_.insert(rule[0]);

    string to = rule.substr(3, rule.size());
    for (char symbol : to) {
        if (isupper(symbol)) {
            non_terminals_.insert(symbol);
        } else {
            alphabet_.insert(symbol);
        }
    }

    Rule new_rule {rule[0], to};
    rules_.push_back(new_rule);
}


const vector <Rule>& Grammar::GetRules() {
    return rules_;
}


Grammar::Grammar(const vector<string>& rules) {
    Rule first_rule {'$', "S"};
    rules_.push_back(first_rule);

    for (const string& new_rule : rules) {
        Grammar::IsRuleCorrect(new_rule);
        AddRule(new_rule);
    }
}