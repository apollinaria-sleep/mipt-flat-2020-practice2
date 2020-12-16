#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <set>


using namespace std;


class IncorrectRule : public exception {
    const char* what() const noexcept override {
        return "Incorrect rule\n";
    }
};


struct Rule {
    char from;
    string to;
    bool operator==(const Rule& another) const;
    bool operator<(const Rule& another) const;
};


class Grammar {
public:
    Grammar() = default;
    explicit Grammar(const vector <string>& rules);
    const vector <Rule>& GetRules();
private:
    static bool IsRuleCorrect(const string& rule);
    void AddRule(const string& rule);
    set <char> alphabet_;
    set <char> non_terminals_;
    vector <Rule> rules_;
};