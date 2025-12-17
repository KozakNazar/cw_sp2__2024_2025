#include <regex>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <iterator>
using namespace std;

int main() {
    ifstream f("EBNF_N1.ebn");
    string s((istreambuf_iterator<char>(f)), {});

    // 1. _
    cout << "Unquoted lexems:\n";
    set<string> u;
    string t = regex_replace(s, regex("\"[^\"]+\""), "");
    regex r1("[a-zA-Z_][a-zA-Z0-9_]*");
    for (sregex_iterator it(t.begin(), t.end(), r1), end; it != end; ++it)
        u.insert((*it)[0]);
    for (const auto& l : u) cout << l << '\n';

    // 3. "_"
    cout << "\nQuoted lexems map:\n";
    regex r2("\"([^\"]+)\"");
    map<string, int> m;
    int id = 1;
    for (sregex_iterator it(s.begin(), s.end(), r2), end; it != end; ++it)
        if (m.insert({ (*it)[1], id }).second)
            cout << '"' << (*it)[1] << "\" -> " << id++ << '\n';

    return 0;
}